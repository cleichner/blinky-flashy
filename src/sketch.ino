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

#define MAX_VELOCITY 1

#define BAUD_RATE 115200

Timer t;

uint16_t intensity = 0;
bool up = true;

bool moving = false;
int8_t rotation = 0;
int8_t xVelocity = 0;
int8_t yVelocity = 0;

int8_t velocityIndex = 0;
int8_t velocityLength = 16;
int8_t yVelocityVals[] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
};
int8_t xVelocityVals[] = {
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
};

void updateVelocity() {
    moving = Car.moving();

    if (velocityIndex < velocityLength) {
        xVelocity = xVelocityVals[velocityIndex];
        yVelocity = yVelocityVals[velocityIndex];
        velocityIndex++;
    } else {
        xVelocity = 0;
        yVelocity = 0;
    }

#if 0
    if (Car.goingForward() && yVelocity < MAX_VELOCITY) {
        yVelocity++;
    } else if (!Car.goingForward() && yVelocity > 0) {
        yVelocity--;
    }

    if (Car.goingBackward() && yVelocity > -MAX_VELOCITY) {
        yVelocity--;
    } else if (!Car.goingBackward() && yVelocity < 0) {
        yVelocity++;
    }

    moving = Car.moving();
    if (Car.goingLeft() && xVelocity < MAX_VELOCITY) {
        xVelocity++;
    } else if (!Car.goingLeft() && xVelocity > 0) {
        xVelocity--;
    }
    if (Car.goingRight() && xVelocity > -MAX_VELOCITY) {
        xVelocity--;
    } else if (!Car.goingRight() && xVelocity < 0) {
        xVelocity++;
    }
#endif
}

uint8_t brightness = 25;
Point sPoints[] = {Point(-1, 1), Point(0, 1), Point(0, 0), Point(1, 0)};
TetrisPiece S(sPoints, THREE_GRID, brightness);

Point iPoints[] = {Point(-1, 0), Point(0, 0), Point(1, 0), Point(2, 0)};
TetrisPiece I(iPoints, FOUR_GRID, brightness*3);

Point insertionPoint(3, 10);
Point center = insertionPoint;

TetrisEnvironment env;

void display() {
    Display.clear();

    TetrisPiece* P = &S;

    P->show(&Display, center, rotation);
    env.show(&Display);

    if (yVelocity < 0 && P->canMoveDown(env, Point(center.x, center.y - 1), rotation)) {
        center.y--;
    }

    if (!P->canMoveDown(env, Point(center.x, center.y - 1), rotation)) {
        P->addToEnvironment(&env, center, rotation);
        center = insertionPoint;
    }

    Display.show();
}

void setup() {
    Serial.begin(BAUD_RATE);
    Serial.println("restart");

    Display.init();
    Car.init();

    t.every(101, updateVelocity);
    t.every(100, display);
}

void loop() {
    t.update();
}

