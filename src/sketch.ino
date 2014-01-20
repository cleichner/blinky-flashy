#include "Display.h"

uint16_t scale = 0;
uint16_t image[NUM_ROWS][NUM_COLS];

void setup() {
    Display.init();
    initialize_image(image);
}

void initialize_image(image) {
    int init = 0;
    for (uint8_t i = 0; i < NUM_ROWS; ++i) {
        for (uint8_t j = 0; j < NUM_COLS; ++j) {
            image[i][j] = init & 0b1;
            init++;
        }
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

void loop()
{
    initialize_image(image);
    brighten(image, scale);
    Display.show(image);
    alternate(image, scale);

    scale++;
    if (scale > 4000) {
        scale = 0;
    }
    delay(33);
}
