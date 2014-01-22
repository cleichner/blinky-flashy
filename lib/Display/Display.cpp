#include <stdint.h>

#include "Display.h"
#include "Tlc5940.h"

void Display_::init() {
    /* Call Tlc.init() to setup the tlcs.
       You can optionally pass an initial PWM value (0 - 4095) for all
       channels.*/
    Tlc.init();
}

void Display_::initialize_image() {
    int init = 0;
    for (uint8_t i = 0; i < NUM_ROWS; ++i) {
        for (uint8_t j = 0; j < NUM_COLS; ++j) {
            image[i][j] = init & 0b1;
            init++;
        }
        init++;
    }
}

void Display_::show() {
    /* I didn't solder the rows in the right order this straightens them out.
     * This can also be generated with a(n) = n + (-1)^n.
     */

    uint8_t row[] = {1, 0, 3, 2, 5, 4, 7, 6, 9, 8, 11, 10};
    for (uint8_t i = 0; i < NUM_ROWS; ++i) {
        for (uint8_t j = 0; j < NUM_COLS; ++j) {
            Tlc.set(row[i] * NUM_COLS + j, image[i][j]);
        }
    }

    /* Tlc.update() sends the data to the TLCs.  This is when the LEDs will
       actually change. */
    Tlc.update();
}

void Display_::brighten(uint16_t scale) {
    for (uint8_t i = 0; i < NUM_ROWS; ++i) {
        for (uint8_t j = 0; j < NUM_COLS; ++j) {
            image[i][j] *= scale;
        }
    }
}

void Display_::alternate(uint16_t scale) {
    for (uint8_t i = 0; i < NUM_ROWS; ++i) {
        for (uint8_t j = 0; j < NUM_COLS; ++j) {
            image[i][j] = scale - image[i][j];
        }
    }
}

Display_ Display;

