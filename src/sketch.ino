#include "Display.h"

uint16_t intensity = 0;

void setup() {
    Display.init();
}


void loop()
{
    static uint8_t vertical_length = 0;
    static uint8_t horizontal_length = 1;
    static bool offset = false;
    static uint16_t wait = 0;

    Display.clear();

    Display.line(1 + vertical_length, 0, 2, VERTICAL, intensity/7);
    Display.line(0, horizontal_length, 2, HORIZONTAL, intensity/7);
    Display.line(1, 0, vertical_length, VERTICAL, intensity);
    Display.line(0, 0, horizontal_length, HORIZONTAL, intensity);

    Display.show();

    if (++wait >= 400) {
        offset = !offset;
        wait = 0;
        horizontal_length++;
        if (horizontal_length & 0x1) {
            vertical_length++;
        }

        if (horizontal_length > NUM_COLS) {
            horizontal_length = 0;
        }
        if (vertical_length > NUM_ROWS) {
            vertical_length = 0;
        }
    }

    if (++intensity >= 4095) {
        intensity = 0;
    }
}
