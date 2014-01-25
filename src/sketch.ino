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

uint16_t intensity = 0;

bool vertical_up = true;
uint8_t vertical_length = 0;

bool horizontal_up = true;
uint8_t horizontal_length = 1;

Timer t;

void update_state() {
    Serial.println("STATE");
    horizontal_length++;
    if (horizontal_length & 0x1) {
        vertical_length++;
    }

    if (horizontal_length > NUM_COLS) {
        horizontal_length = 1;
    }

    if (vertical_length > NUM_ROWS) {
        vertical_length = 0;
    }

    if (horizontal_length == 1 && vertical_length == 0) {
        intensity = 0;
    }
}

void brighten() {
    Serial.print("*");
    if (intensity < 4095) {
        intensity++;
    } else {
        intensity = 0;
    }
    Display.show();
}

void setup() {
    Serial.begin(9600);
    Display.init();
    Car.init();

    intensity = 2000;
//    t.every(1000, update_state);
//    t.every(50, brighten);
}

void loop()
{
    uint8_t centerX = 4;
    uint8_t centerY = 4;

    Display.clear();
    if (Car.goingForward()) {
        centerY += 1;
    }

    if (Car.goingBackward()) {
        centerY -= 1;
    }

    if (Car.goingLeft()) {
        centerX -= 1;
    }

    if (Car.goingRight()) {
        centerX += 1;
    }

    Display.line(centerY, 0, 8, HORIZONTAL, intensity);
    Display.line(0, centerX, 12, VERTICAL, intensity);

    Display.show();

    t.update();
    delay(33);
}
