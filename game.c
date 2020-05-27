/* Author: James Napier (jhn27) & Simon Lorimer (sal180)
 * Date: 10 Oct 2019
 * Descr: Main game program that calls other functions to run game
 */

#include "system.h"
#include <stdio.h>
#include <stdlib.h>
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "ledmat.h"
#include "timer.h"
#include <avr/io.h>
#include "turndisplay.h"
#include "turnupdate.h"
#include "turnlogic.h"

#define GAME_INIT 101

#define START_GAME 11
#define WAIT_GAME 22

#define GAME_LOST 33
#define GAME_WON 44

#define ROUND_WON 55

#define MESSAGE_RATE 2
#define LOOP_RATE 500

#define MIN_TIME 500
#define DECREASE_TIMER 0.1


//Initialise all drivers
void init_all(void)
{
    system_init();

    ir_uart_init();

    timer_init();

    tinygl_init (LOOP_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
}

//Counter that will also update tinygl character
void timer_delay (uint16_t milliseconds)
{
    TCNT1 = 0;

    while (TCNT1 < (milliseconds/0.000128)/1000) {
        tinygl_update();
        continue;
    }
}

//Decrease timer by DECREASE_TIMER as a percentage of current remaining time
int lower_timer(int time)
{
    if (time >= MIN_TIME) {
        time -= (DECREASE_TIMER * time);
    }
    return time;
}

//Start game and returns who starts and who waits
char init_game(void)
{
    tinygl_text("PUSH TO START");

    while(1) {

        navswitch_update ();
        tinygl_update();

        //Player 1 starts
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            ir_uart_putc(WAIT_GAME);
            return START_GAME;
        }

        //Player 2 waits
        else if (ir_uart_read_ready_p()) {
            if (ir_uart_getc() == WAIT_GAME) {
                return WAIT_GAME;
            }
        }
    }
}

//While navswitch has not been pressed, display LOSER
void game_lost(void)
{
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text("LOSER");

    int losing = 1;

    while (losing) {
        tinygl_update();
        navswitch_update();
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            losing = 0;
        }
    }
}

//While navswitch has not been pressed, display LOSER
void game_won(void)
{
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text("WINNER");

    int winning = 1;

    while (winning) {
        tinygl_update();
        navswitch_update();
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            winning = 0;
        }
    }
}

/* Wait state for waiting controller during turn.
 * This will loop until GAME_WON or START_GAME is received.
 */
char wait_game(void)
{
    char check;
    tinygl_text("W");
    while (1) {
        tinygl_update();
        if (ir_uart_read_ready_p()) {
            check = ir_uart_getc();
            if (check == GAME_WON) {
                return GAME_WON;
            } else if (check == START_GAME) {
                return START_GAME;
            }
        }
    }
}

/* Main function of the program.
 * Loops through supporting functions to play game.
 * Handles what state the game is currently in.
 * Will loop indefinitely.
 */
int main (void)
{
    uint8_t game_status = 0;

    float dot_timer = 4000;

    int rounds_won = 0;

    init_all();

    while (1) {

        game_status = init_game();

        //game started loop
        while ((game_status != GAME_LOST) && (game_status != GAME_WON)) {
            tinygl_text_mode_set (TINYGL_TEXT_MODE_STEP);

            //Player's turn
            while (game_status == START_GAME) {

                game_status = play_game(dot_timer, rounds_won);
                dot_timer = lower_timer(dot_timer);

                if (game_status == ROUND_WON) {
                    rounds_won += 1;
                    ir_uart_putc(START_GAME);
                    game_status = WAIT_GAME;
                } else if (game_status == GAME_LOST) {
                    ir_uart_putc(GAME_WON);
                }
            }

            //Player wait
            while (game_status == WAIT_GAME) {
                game_status = wait_game();
            }
        }
        //Win or lose state
        if (game_status == GAME_LOST) {
            game_lost();
        } else {
            game_won();
        }

        //Reset values to default for next game
        dot_timer = 4000;
        rounds_won = 0;
        game_status = GAME_INIT;
    }
}
