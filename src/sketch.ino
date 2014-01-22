#include "Display.h"

uint16_t intensity = 0;

void setup() {
    Display.init();
}

void loop()
{
    static bool offset = false;
    static uint16_t wait = 0;

    Display.clear();
    Display.line(4, VERTICAL, intensity);
    Display.line(3, VERTICAL, intensity);
    Display.line(4, HORIZONTAL, intensity);
    Display.line(5, HORIZONTAL, intensity);
    //Display.checkerboard(intensity, offset);
    Display.show();

    if (++wait >= 400) {
        offset = !offset;
        wait = 0;
    }

    if (++intensity >= 4095) {
        intensity = 0;
    }
}
