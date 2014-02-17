/*
    blinky-flashy firmware -- Controls LED display on RC car.
    Copyright (C) 2014 Chas Leichner

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Car.h"
#include "Display.h"
#include "Tetris.h"
#include "Timer.h"

#define UPDATE_PERIOD 2000
#define MAX_INTENSITY 3750
#define MIN_INTENSITY 20

#define BAUD_RATE 115200

Timer t;

bool moving = false;
uint16_t intensity = 0;
bool up = true;

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

int8_t r = 0;
void rotate() {
    r++;
    r %=  4;
}

int8_t r2 = 0;
void rotate2() {
    r2++;
    r2 %= 4;
}

uint8_t brightness = 25;
Point sPoints[] = {Point(-1, 1), Point(0, 1), Point(0, 0), Point(1, 0)};
TetrisPiece S(sPoints, THREE_GRID, brightness);

Point iPoints[] = {Point(-1, 0), Point(0, 0), Point(1, 0), Point(2, 0)};
TetrisPiece I(iPoints, FOUR_GRID, brightness);

void display() {
    Display.clear();

    Point center(4,4);
    S.show(&Display, center, r);

    Point other(4,8);
    I.show(&Display, other, 3-r2);

    Display.show();
}

void setup() {
    Serial.begin(BAUD_RATE);
    Display.init();
    Car.init();

    t.every(20, display);
    t.every(500, rotate);
    t.every(509, rotate2);

    t.every(100, updateY);
    t.every(120, updateX);
    Serial.println("restart");
}

void loop() {
    t.update();
}

