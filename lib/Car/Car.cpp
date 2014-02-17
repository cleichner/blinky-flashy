#include <avr/io.h>

#include "Car.h"

const int forwardInput = 5;  // PD5 - D5 - Pin 11
const int backwardInput = 6; // PD6 - D6 - Pin 12
const int leftInput = 7;     // PD7 - D7 - Pin 13
const int rightInput = 0;    // PB0 - D8 - Pin 14

void CarCls::init() {
    // Set all input pins as inputs
    DDRD &= (~(1 << forwardInput) &
             ~(1 << backwardInput) &
             ~(1 << rightInput));
    DDRB &= (~(1 << rightInput));
}

bool CarCls::goingForward() {
    return !(PIND & (1 << forwardInput));
}

bool CarCls::goingBackward() {
    return !(PIND & (1 << backwardInput));
}

bool CarCls::goingLeft() {
    return !(PIND & (1 << leftInput));
}

bool CarCls::goingRight() {
    return !(PINB & (1 << rightInput));
}

bool CarCls::moving() {
    return goingForward() || goingBackward() || goingLeft() || goingRight();
}

CarCls Car;
