/* Author: James Napier (jhn27) & Simon Lorimer (sal180)
 * Date: 14 Oct 2019
 * Descr: Module to handle turn logic
 * */

#ifndef TURNLOGIC_H
#define TURNLOGIC_H

#define GAME_INIT 101

#define START_GAME 11
#define WAIT_GAME 22

#define GAME_LOST 33
#define GAME_WON 44

#define ROUND_WON 55

#include <stdlib.h>
#include "turnupdate.h"   
#include "turndisplay.h"
#include "system.h"
#include <avr/io.h>  

int rng_number(void);

int play_game(float timer, int rounds_won);

#endif

