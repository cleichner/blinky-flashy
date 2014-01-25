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


uint16_t intensity = 0;

void brighten() {
//    Serial.println(intensity);
    if (++intensity >= 4095) {
        intensity = 0;
    }
}

uint8_t centerX = 4;
uint8_t centerY = 6;

void updateY() {
    if (Car.goingForward() && centerY < 11) {
        centerY++;
    } else if (!Car.goingForward() && centerY > 6) {
        centerY--;
    }

    if (Car.goingBackward() && centerY > 1) {
        centerY--;
    } else if (!Car.goingBackward() && centerY < 6) {
        centerY++;
    }
}

void updateX() {
    if (Car.goingLeft() && centerX < 6) {
        centerX++;
    } else if (!Car.goingLeft() && centerX > 4) {
        centerX--;
    }

    if (Car.goingRight() && centerX > 1) {
        centerX--;
    } else if (!Car.goingRight() && centerX < 4) {
        centerX++;
    }
}

void setup() {
    Serial.begin(9600);
    Display.init();
    Car.init();

//    t.every(1000, update_state);
    t.every(30, brighten);
    t.every(100, updateY);
    t.every(120, updateX);
}

void loop()
{
    Display.clear();

    Display.line(centerY, 0, 8, HORIZONTAL, intensity);
    Display.line(centerY-1, 0, 8, HORIZONTAL, intensity);

    Display.line(0, centerX, 12, VERTICAL, intensity);
    Display.line(0, centerX-1, 12, VERTICAL, intensity);

    Display.show();

    t.update();
    delay(33);
}
