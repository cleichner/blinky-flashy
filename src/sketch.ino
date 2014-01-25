#include "Display.h"
#include "Timer.h"

#define UPDATE_PERIOD 2000
// every, every (with repeat), after,

const int forwardInput = 5;
const int backwardInput = 6;
const int leftInput = 7;
const int rightInput = 8;

class CarCls {
    public:
        void init();
        bool goingForward();
        bool goingBackward();
        bool goingLeft();
        bool goingRight();
};

void CarCls::init() {
    pinMode(forwardInput, INPUT);      // sets the digital pin as output
    pinMode(backwardInput, INPUT);      // sets the digital pin as output
    pinMode(leftInput, INPUT);      // sets the digital pin as output
    pinMode(rightInput, INPUT);      // sets the digital pin as output

}

bool CarCls::goingForward() {
    return !digitalRead(forwardInput);
}

bool CarCls::goingBackward() {
    return !digitalRead(backwardInput);
}

bool CarCls::goingLeft() {
    return !digitalRead(leftInput);
}

bool CarCls::goingRight() {
    return !digitalRead(rightInput);
}

CarCls Car;
Timer t;

bool moving = false;

uint16_t intensity = 0;
bool up = true;
void pulse() {
    if (!moving) {
        if (up) {
            intensity += 1;
            if (intensity >= 3750) {
                up = false;
            }
            if (intensity > 500) {
                intensity += 5;
            }
            if (intensity > 1000) {
                intensity += 5;
            }
            if (intensity > 2000) {
                intensity += 5;
            }
        } else {
            intensity -= 1;
            if (intensity <= 20) {
                up = true;
            }
            if (intensity > 500) {
                intensity -= 5;
            }
            if (intensity > 1000) {
                intensity -= 5;
            }
            if (intensity > 2000) {
                intensity -= 5;
            }
        }
    } else {
        if (intensity <= 3750) {
            intensity += 1;
            if (intensity > 500) {
                intensity += 5;
            }
            if (intensity > 1000) {
                intensity += 5;
            }
            if (intensity > 2000) {
                intensity += 5;
            }
        }
    }
}

uint16_t movingTime = 0;
void updateMovingTime() {
    if (moving && movingTime < 3750) {
        movingTime += 25;
    } else if (movingTime > 0) {
        movingTime -= 25;
    }
}

uint8_t centerX = 4;
uint8_t centerY = 6;

void updateY() {
    if (Car.goingForward() && centerY < 11) {
        moving = true;
        centerY++;
    } else if (!Car.goingForward() && centerY > 6) {
        moving = false;
        centerY--;
    }

    if (Car.goingBackward() && centerY > 1) {
        moving = true;
        centerY--;
    } else if (!Car.goingBackward() && centerY < 6) {
        moving = false;
        centerY++;
    }
}

void updateX() {
    if (Car.goingLeft() && centerX < 7) {
        moving = true;
        centerX++;
    } else if (!Car.goingLeft() && centerX > 4) {
        moving = false;
        centerX--;
    }
    if (Car.goingRight() && centerX > 1) {
        moving = true;
        centerX--;
    } else if (!Car.goingRight() && centerX < 4) {
        moving = false;
        centerX++;
    }
}

void display() {
    Display.clear();

    for (int i = 0; i < 12; i++) {
        Display.line(i, 0, 8, HORIZONTAL, movingTime);
    }

    Display.line(centerY, 0, 8, HORIZONTAL, intensity);
    Display.line(centerY-1, 0, 8, HORIZONTAL, intensity);

    Display.line(0, centerX, 12, VERTICAL, intensity);
    Display.line(0, centerX-1, 12, VERTICAL, intensity);

    Display.show();
}


void setup() {
    Serial.begin(9600);
    Display.init();
    Car.init();

    t.every(3, display);
    t.every(3, pulse);
    t.every(100, updateY);
    t.every(120, updateX);
    t.every(200, updateMovingTime);
}

void loop()
{
    t.update();
}
