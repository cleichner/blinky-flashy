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
    r = r % 4;
}

struct Point {
    int8_t x;
    int8_t y;
    Point(int8_t x, int8_t y) : x(x), y(y) { }
    Point operator +(const Point& p) {
        return Point(x + p.x, y + p.y);
    }
    Point rotate(int8_t n) {
        if (n == 0) {
            return *this;
        } else {
            return Point(-y, x).rotate(n - 1);
        }
    }
};

#define SQUARES_IN_PIECE 4

void display() {
    Display.clear();

    uint8_t brightness = 200;

    Point points[SQUARES_IN_PIECE] = {
        Point(-1, 1), Point(0, 1), Point(0, 0), Point(1, 0)
    };
    Point center(4,4);
    for (int8_t i = 0; i < SQUARES_IN_PIECE; i++) {
        Point p = center + points[i].rotate(r);
        Display.point(p.x, p.y, brightness);
    }

    Point other(4,8);
    for (int8_t i = 0; i < SQUARES_IN_PIECE; i++) {
        Point p = other + points[i].rotate(3 - r);
        Display.point(p.x, p.y, brightness);
    }

    Display.show();
}

void setup() {
    Serial.begin(BAUD_RATE);
    Display.init();
    Car.init();

    t.every(20, display);
    t.every(500, rotate);
    // Uncomment to log all state variables
    // t.every(10, log);
    t.every(100, updateY);
    t.every(120, updateX);
    Serial.println("restart");
}

void loop() {
    t.update();
}

