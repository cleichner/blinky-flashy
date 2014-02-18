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
int8_t xVelocity = 0;
int8_t yVelocity = 0;

void updateY() {
    moving = Car.moving();

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
}

void updateX() {
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
}

uint8_t brightness = 25;
Point sPoints[] = {Point(-1, 1), Point(0, 1), Point(0, 0), Point(1, 0)};
TetrisPiece S(sPoints, THREE_GRID, brightness);

Point iPoints[] = {Point(-1, 0), Point(0, 0), Point(1, 0), Point(2, 0)};
TetrisPiece I(iPoints, FOUR_GRID, brightness*3);

Point insertionPoint(3, 10);
Point center = insertionPoint;

TetrisEnvironment env;

bool canRotate = true;
int8_t r = 0;
void rotate() {
    if (canRotate) {
        r++;
        r %=  4;
    }
}

void update() {
    if (center.y > 2) {
        center.y -= 1;
    } else {
        center = insertionPoint;
    }
}

void display() {
    Display.clear();

    TetrisPiece* P = &S;

    P->show(&Display, center, r);
    env.show(&Display);

    if (yVelocity < 0 && P->canMoveDown(Point(center.x, center.y - 1), r)) {
        center.y--;
    }

    if (!P->canMoveDown(Point(center.x, center.y - 1), r)) {
        P->addToEnvironment(&env, center, r);
        center = insertionPoint;
    }
/*
    if (P->inside(center, r) && P->inside(Point(center.x - 1, center.y), r)) {
        center.x--;
    } else {
        canRotate = false;
    }
    */

    Display.show();
}

void setup() {
    Serial.begin(BAUD_RATE);
    Display.init();
    Car.init();

//    I.addToEnvironment(&env, insertionPoint, 2);

    t.every(100, display);
//    t.every(200, rotate);

    //t.every(600, update);
    t.every(10, updateY);
    t.every(10, updateX);
    Serial.println("restart");
}

void loop() {
    t.update();
}

