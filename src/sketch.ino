#include "Display.h"

uint16_t scale = 0;
uint16_t image[NUM_ROWS][NUM_COLS];

void setup() {
    Display.init();
    initialize_image(image);
}

void initialize_image(uint16_t image[NUM_ROWS][NUM_COLS]) {
    int init = 0;
    for (uint8_t i = 0; i < NUM_ROWS; ++i) {
        for (uint8_t j = 0; j < NUM_COLS; ++j) {
            image[i][j] = init & 0b1;
            init++;
        }
        init++;
    }
}

void brighten(uint16_t image[NUM_ROWS][NUM_COLS], uint16_t scale) {
    for (uint8_t i = 0; i < NUM_ROWS; ++i) {
        for (uint8_t j = 0; j < NUM_COLS; ++j) {
            image[i][j] *= scale;
        }
    }
}

void alternate(uint16_t image[NUM_ROWS][NUM_COLS], uint16_t scale) {
    for (uint8_t i = 0; i < NUM_ROWS; ++i) {
        for (uint8_t j = 0; j < NUM_COLS; ++j) {
            image[i][j] = scale - image[i][j];
        }
    }
}

uint16_t wait = 0;

void loop()
{
    initialize_image(image);
    brighten(image, scale);

    if (wait < 200) {
        alternate(image, scale);
    }

    Display.show(image);

    wait++;
    if (wait > 400) {
        wait = 0;
    }

    scale++;
    if (scale > 4000) {
        scale = 0;
    }
//    delay(33);
}
