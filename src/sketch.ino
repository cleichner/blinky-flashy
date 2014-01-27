#include "Car.h"
#include "Display.h"
#include "Timer.h"

#define UPDATE_PERIOD 2000
#define MAX_INTENSITY 3750
#define MIN_INTENSITY 20

#define BAUD_RATE 115200

Timer t;

bool moving = false;
uint16_t intensity = 0;
bool up = true;

void pulse() {
    if (!moving) {
        if (up) {
            intensity += 1;
            if (intensity >= MAX_INTENSITY) {
                up = false;
            }
            if (intensity > MAX_INTENSITY/7) {
                intensity += 5;
            }
            if (intensity > MAX_INTENSITY/3) {
                intensity += 5;
            }
            if (intensity > MAX_INTENSITY/2) {
                intensity += 5;
            }
        } else {
            intensity -= 1;
            if (intensity <= MIN_INTENSITY) {
                up = true;
            }
            if (intensity > MAX_INTENSITY/7) {
                intensity -= 5;
            }
            if (intensity > MAX_INTENSITY/3) {
                intensity -= 5;
            }
            if (intensity > MAX_INTENSITY/2) {
                intensity -= 5;
            }
        }
    } else {
        if (intensity <= MAX_INTENSITY) {
            intensity += 1;
            if (intensity > MAX_INTENSITY/7) {
                intensity += 5;
            }
            if (intensity > MAX_INTENSITY/3) {
                intensity += 5;
            }
            if (intensity > MAX_INTENSITY/2) {
                intensity += 5;
            }
        }
    }
}


int8_t centerX = 0;
int8_t centerY = 0;

void updateY() {
    if (Car.goingForward() && centerY < NUM_ROWS) {
        moving = true;
        centerY++;
    } else if (!Car.goingForward() && centerY > 0) {
        moving = false;
        centerY--;
    }

    if (Car.goingBackward() && centerY > -NUM_ROWS) {
        moving = true;
        centerY--;
    } else if (!Car.goingBackward() && centerY < 0) {
        moving = false;
        centerY++;
    }
}

void updateX() {
    if (Car.goingLeft() && centerX < NUM_COLS - 1) {
        moving = true;
        centerX++;
    } else if (!Car.goingLeft() && centerX > 0) {
        moving = false;
        centerX--;
    }
    if (Car.goingRight() && centerX > -NUM_COLS) {
        moving = true;
        centerX--;
    } else if (!Car.goingRight() && centerX < 0) {
        moving = false;
        centerX++;
    }
}

void display() {
    Display.clear();

    for (int8_t i = 0; i < centerY; i++) {
        if (i >= 0) {
            Display.line(i, 0, NUM_COLS, HORIZONTAL, intensity/2);
        }
    }
    for (int8_t i = (NUM_ROWS - 1); i > (NUM_ROWS - 1) + centerY; i--) {
        if (i >= 0) {
            Display.line(i, 0, NUM_COLS, HORIZONTAL, intensity/2);
        }
    }

    for (int8_t i = 1; i < centerX; i++) {
        if (i != 0 && i != (NUM_COLS - 1)) {
            Display.line(0, i, NUM_ROWS, VERTICAL, intensity/2);
        }
    }
    for (int8_t i = (NUM_COLS - 1); i > (NUM_COLS - 1) + centerX; i--) {
        if (i != 0 && i != (NUM_COLS - 1)) {
            Display.line(0, i, NUM_ROWS, VERTICAL, intensity/2);
        }
    }

    Display.line(0, 0, NUM_ROWS, VERTICAL, intensity/2);
    Display.line(0, (NUM_COLS - 1), NUM_ROWS, VERTICAL, intensity/2);

    Display.show();
}

void log() {
    Serial.print(centerX);
    Serial.print(" ");
    Serial.print(centerY);
    Serial.print(" ");
    Serial.print(intensity);
    Serial.print(" ");
    Serial.print(up);
    Serial.print(" ");
    Serial.println(moving);

}

void setup() {
    Serial.begin(BAUD_RATE);
    Display.init();
    Car.init();

    t.every(3, display);
    t.every(10, pulse);
    // Uncomment to log all state variables
    // t.every(10, log);
    t.every(100, updateY);
    t.every(120, updateX);
    Serial.println("restart");
}

void loop() {
    t.update();
}

