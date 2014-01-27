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


int8_t centerX = 0;
int8_t centerY = 0;

void updateY() {
    if (Car.goingForward() && centerY < 12) {
        moving = true;
        centerY++;
    } else if (!Car.goingForward() && centerY > 0) {
        moving = false;
        centerY--;
    }

    if (Car.goingBackward() && centerY > -12) {
        moving = true;
        centerY--;
    } else if (!Car.goingBackward() && centerY < 0) {
        moving = false;
        centerY++;
    }
}

void updateX() {
    if (Car.goingLeft() && centerX < 7) {
        moving = true;
        centerX++;
    } else if (!Car.goingLeft() && centerX > 0) {
        moving = false;
        centerX--;
    }
    if (Car.goingRight() && centerX > -8) {
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
            Display.line(i, 0, 8, HORIZONTAL, intensity/2);
        }
    }
    for (int8_t i = 11; i > 11 + centerY; i--) {
        if (i >= 0) {
            Display.line(i, 0, 8, HORIZONTAL, intensity/2);
        }
    }

    for (int8_t i = 1; i < centerX; i++) {
        if (i != 0 && i != 7) {
            Display.line(0, i, 12, VERTICAL, intensity/2);
        }
    }
    for (int8_t i = 7; i > 7 + centerX; i--) {
        if (i != 0 && i != 7) {
            Display.line(0, i, 12, VERTICAL, intensity/2);
        }
    }

    Display.line(0, 0, 12, VERTICAL, intensity/2);
    Display.line(0, 7, 12, VERTICAL, intensity/2);

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
    Serial.begin(9600);
    Display.init();
    Car.init();

    t.every(3, display);
    t.every(10, pulse);
    //t.every(10, log);
    t.every(100, updateY);
    t.every(120, updateX);
    //t.every(200, updateMovingTime);
    Serial.println("restart");
}

void loop() {
    t.update();
}

