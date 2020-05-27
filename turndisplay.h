/* Author: James Napier (jhn27) & Simon Lorimer (sal180)
 * Date: 10 Oct 2019
 * Descr: Module to handle display of turn with move
 * and timer using bitmaps
 * */
#ifndef TURNDISPLAY_H
#define TURNDISPLAY_H

#include "system.h"
#include "pacer.h"
#include "ledmat.h"

// Global constants for each symbol bitmap

//Up
extern const uint8_t bitmapUp[];

//Down
extern const uint8_t bitmapDown[];

//Left
extern const uint8_t bitmapLeft[];

//Right
extern const uint8_t bitmapRight[];

//Centre 
extern const uint8_t bitmapCentre[];

//Overwrite passed in bitmap for timer with number of dots put in
void get_time_bitmap(uint8_t* bitmap, uint8_t numberDots);

//Combine bitmap for number timer and symbol by overwriting bitmap passed in
void get_combined_bitmap(uint8_t* bitmap, const uint8_t* symbolBitmap, uint8_t numberDots);

//Display turn bitmap using ledmat driver. Does this once only
void display_turn(uint8_t*turnBitmap); 

#endif
