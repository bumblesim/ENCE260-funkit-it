/* Author: James Napier (jhn27) & Simon Lorimer (sal180)
 * Date: 14 Oct 2019
 * Descr: Module to handle updating while player's turn is happening
 * */
 
#include "system.h"
#include "navswitch.h"
#include "turndisplay.h"
#include <avr/io.h>

int game_delay_north (uint16_t milliseconds, uint8_t* bitmap)
{

    TCNT1 = 0;
    while (TCNT1 < (milliseconds/0.000128)/1000) {
        navswitch_update();
        display_turn(bitmap);
        if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
            return 1;
        } else if (navswitch_push_event_p(NAVSWITCH_PUSH) || navswitch_push_event_p(NAVSWITCH_EAST) || navswitch_push_event_p(NAVSWITCH_WEST) || navswitch_push_event_p(NAVSWITCH_SOUTH)) {
            return 0;
        }
    }
    return -1;
}

int game_delay_south (uint16_t milliseconds, uint8_t* bitmap)
{

    TCNT1 = 0;
    while (TCNT1 < (milliseconds/0.000128)/1000) {
        navswitch_update();
        display_turn(bitmap);
        if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
            return 1;
        } else if (navswitch_push_event_p(NAVSWITCH_PUSH) || navswitch_push_event_p(NAVSWITCH_EAST) || navswitch_push_event_p(NAVSWITCH_WEST) || navswitch_push_event_p(NAVSWITCH_NORTH)) {
            return 0;
        }
    }
    return -1;
}

int game_delay_east (uint16_t milliseconds, uint8_t* bitmap)
{

    TCNT1 = 0;
    while (TCNT1 < (milliseconds/0.000128)/1000) {
        navswitch_update();
        display_turn(bitmap);
        if (navswitch_push_event_p(NAVSWITCH_EAST)) {
            return 1;
        } else if (navswitch_push_event_p(NAVSWITCH_PUSH) || navswitch_push_event_p(NAVSWITCH_SOUTH) || navswitch_push_event_p(NAVSWITCH_WEST) || navswitch_push_event_p(NAVSWITCH_NORTH)) {
            return 0;
        }
    }
    return -1;
}

int game_delay_west (uint16_t milliseconds, uint8_t* bitmap)
{

    TCNT1 = 0;
    while (TCNT1 < (milliseconds/0.000128)/1000) {
        navswitch_update();
        display_turn(bitmap);
        if (navswitch_push_event_p(NAVSWITCH_WEST)) {
            return 1;
        } else if (navswitch_push_event_p(NAVSWITCH_PUSH) || navswitch_push_event_p(NAVSWITCH_SOUTH) || navswitch_push_event_p(NAVSWITCH_EAST) || navswitch_push_event_p(NAVSWITCH_NORTH)) {
            return 0;
        }
    }
    return -1;
}

int game_delay_push (uint16_t milliseconds, uint8_t* bitmap)
{

    TCNT1 = 0;
    while (TCNT1 < (milliseconds/0.000128)/1000) {
        navswitch_update();
        display_turn(bitmap);
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            return 1;
        } else if (navswitch_push_event_p(NAVSWITCH_NORTH) || navswitch_push_event_p(NAVSWITCH_EAST) || navswitch_push_event_p(NAVSWITCH_WEST) || navswitch_push_event_p(NAVSWITCH_SOUTH)) {
            return 0;
        }
    }
    return -1;
}
