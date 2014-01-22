#include "Display.h"

uint16_t scale = 0;

void setup() {
    Display.init();
}


uint16_t wait = 0;

void loop()
{
    Display.initialize_image();
    Display.brighten(scale);

    if (wait < 200) {
        Display.alternate(scale);
    }

    Display.show();

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
