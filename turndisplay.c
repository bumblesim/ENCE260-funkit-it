/* Author: James Napier (jhn27) & Simon Lorimer (sal180)
 * Date: 10 Oct 2019
 * Descr: Module to create and display turn bitmaps
 * */

#include "system.h"
#include "pacer.h"
#include "ledmat.h"


// Global constants for each symbol bitmap

//Left
const uint8_t bitmapLeft[] = {
    0x00, 0x10, 0x28, 0x44, 0x00
};

//Right
const uint8_t bitmapRight[] = {
    0x00, 0x44, 0x28, 0x10, 0x00
};

//Down
const uint8_t bitmapDown[] = {
    0x08, 0x10, 0x20, 0x10, 0x08
};

//Up
const uint8_t bitmapUp[] = {
    0x20, 0x10, 0x08, 0x10, 0x20
};

//Centre
const uint8_t bitmapCentre[] = {
    0x38, 0x44, 0x44, 0x44,  0x38
};

//Overwrite passed in bitmap for timer with number of dots put in
void get_time_bitmap(uint8_t* bitmap, uint8_t numberDots)
{
    for (uint8_t i = 0; i < 5; i++) {

        if (i < numberDots) {
            bitmap[i] = 0x01;
        } else {
            bitmap[i] = 0x00;
        }

    }
}

//Combine bitmap for number timer and symbol by overwriting bitmap passed in
void get_combined_bitmap(uint8_t* bitmap, const uint8_t* symbolBitmap, uint8_t numberDots)
{
    //get timer to merge bitmaps
    uint8_t timerBitmap[] = {0x00, 0x00, 0x00, 0x00, 0x00};

    get_time_bitmap(timerBitmap, numberDots);

    for (uint8_t i = 0; i < 5; i++) {
        bitmap[i] = timerBitmap[i] | symbolBitmap[i];
    }
}

//Display turn bitmap using ledmat driver. Does this once only
void display_turn(uint8_t* turnBitmap)
{
    for (uint8_t i = 0; i < 5; i++){
        ledmat_display_column (turnBitmap[i], i);

    }
}
