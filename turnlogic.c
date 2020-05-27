/* Author: James Napier (jhn27) & Simon Lorimer (sal180)
 * Date: 14 Oct 2019
 * Descr: Module to handle turn logic
 * */

#include <stdlib.h>
#include "turnupdate.h"
#include "turndisplay.h"
#include "system.h"
#include <avr/io.h>

#define GAME_INIT 101

#define START_GAME 11
#define WAIT_GAME 22

#define GAME_LOST 33
#define GAME_WON 44

#define ROUND_WON 55

int rng_number(void)
{
    srand(TCNT1 * 1000000000);
    return rand();
}

int play_game(float timer, int rounds_won)
{
    int number = (rounds_won + rng_number()) % 5;

    int count = 5;

    int result = -1;

    uint8_t gameBitmap[] = {0x00, 0x00, 0x00, 0x00, 0x00};

    if (number == 0) {
        // north
        while (count > 0) {

            get_combined_bitmap(gameBitmap, bitmapUp, count);
            result = game_delay_north(timer, gameBitmap);
            if (result == 1) {
                return ROUND_WON;
            } else if (result == 0) {
                return GAME_LOST;
            }
            count -= 1;
        }
    } else if (number == 1) {
        // south
        while (count > 0) {

            get_combined_bitmap(gameBitmap, bitmapDown, count);
            result = game_delay_south(timer, gameBitmap);
            if (result == 1) {
                return ROUND_WON;
            } else if (result == 0) {
                return GAME_LOST;
            }
            count -= 1;
        }
    } else if (number == 2) {
        // east
        while (count > 0) {

            get_combined_bitmap(gameBitmap, bitmapRight, count);
            result = game_delay_east(timer, gameBitmap);
            if (result == 1) {
                return ROUND_WON;
            } else if (result == 0) {
                return GAME_LOST;
            }
            count -= 1;
        }
    } else if (number == 3) {
        // west
        while (count > 0) {

            get_combined_bitmap(gameBitmap, bitmapLeft, count);
            result = game_delay_west(timer, gameBitmap);
            if (result == 1) {
                return ROUND_WON;
            } else if (result == 0) {
                return GAME_LOST;
            }
            count -= 1;
        }
    } else if (number == 4) {
        // button push
        while (count > 0) {

            get_combined_bitmap(gameBitmap, bitmapCentre, count);
            result = game_delay_push(timer, gameBitmap);
            if (result == 1) {
                return ROUND_WON;
            } else if (result == 0) {
                return GAME_LOST;
            }
            count -= 1;
        }
    }

    return GAME_LOST;
}
