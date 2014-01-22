#include <stdint.h>

#include "Display.h"
#include "Tlc5940.h"

void DisplayCls::init() {
    /* Call Tlc.init() to setup the tlcs.
       You can optionally pass an initial PWM value (0 - 4095) for all
       channels.*/
    Tlc.init();
}

void DisplayCls::line(uint8_t index, orientation_t orientation,
                      uint16_t intensity) {
    uint8_t limit = NUM_ROWS;
    if (orientation == HORIZONTAL) {
       limit = NUM_COLS;
    }
    for (uint8_t i = 0; i < limit; ++i) {
        if (orientation == VERTICAL) {
            image[i][index] = intensity;
        } else {
            image[index][i] = intensity;
        }
    }
}

void DisplayCls::clear() {
    for (uint8_t i = 0; i < NUM_ROWS; ++i) {
        for (uint8_t j = 0; j < NUM_COLS; ++j) {
            image[i][j] = 0;
        }
    }
}

void DisplayCls::checkerboard(uint16_t intensity, bool offset) {
    uint8_t init = 0;
    if (offset) {
        init = 1;
    }
    for (uint8_t i = 0; i < NUM_ROWS; ++i) {
        for (uint8_t j = 0; j < NUM_COLS; ++j) {
            image[i][j] = intensity * (init & 0b1);
            init++;
        }
        init++;
    }
}

void DisplayCls::show() {
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

void DisplayCls::alternate(uint16_t intensity) {
    for (uint8_t i = 0; i < NUM_ROWS; ++i) {
        for (uint8_t j = 0; j < NUM_COLS; ++j) {
            image[i][j] = intensity - image[i][j];
        }
    }
}

DisplayCls Display;

