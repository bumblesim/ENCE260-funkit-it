/* Author: James Napier (jhn27) & Simon Lorimer (sal180)
 * Date: 14 Oct 2019
 * Descr: Module to handle updating while player's turn is happening
 * */

#ifndef TURN_H
#define TURN_H

#include "system.h"
#include "navswitch.h"
#include "turndisplay.h"    
#include <avr/io.h>

int game_delay_north (uint16_t milliseconds, uint8_t* bitmap);

int game_delay_south (uint16_t milliseconds, uint8_t* bitmap);

int game_delay_east (uint16_t milliseconds, uint8_t* bitmap);

int game_delay_west (uint16_t milliseconds, uint8_t* bitmap);

int game_delay_push (uint16_t milliseconds, uint8_t* bitmap);

#endif
