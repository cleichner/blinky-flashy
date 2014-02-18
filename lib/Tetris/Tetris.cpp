#include "Display.h"
#include "Tetris.h"

#include <stdint.h>

void TetrisEnvironment::show(DisplayCls* d) {
    for (int8_t x = 0; x < NUM_COLS; x++) {
        for (int8_t y = 0; y < NUM_ROWS; y++) {
            if (env[x][y]) {
                d->point(x, y, env[x][y]);
            }
        }
    }
}

Point rotate(Point p, RotationGrid grid, int8_t n) {
    if (n == 0) {
        return p;
    } else {
        return rotate(Point(-p.y, p.x - grid), grid, n - 1);
    }
}

void TetrisPiece::show(DisplayCls* d, const Point& center, int8_t rotation) {
    for (int8_t i = 0; i < SQUARES_IN_PIECE; i++) {
        Point p = center + rotate(piece[i], grid, rotation);
        d->point(p.x, p.y, brightness);
    }
}

// should replace with can rotate and can move to separately
bool TetrisPiece::canMoveDown(const Point& center, int8_t rotation) {
    for (int8_t i = 0; i < SQUARES_IN_PIECE; i++) {
        Point p = center + rotate(piece[i], grid, rotation);
        if (p.x < 0 || p.y < 0) {
            return false;
        }

        if (p.x > NUM_COLS - 1 || p.y > NUM_ROWS - 1) {
            return false;
        }
    }
    return true;
}

void TetrisPiece::addToEnvironment(TetrisEnvironment* env, const Point& center,
                                   int8_t rotation) {
    for (int8_t i = 0; i < SQUARES_IN_PIECE; i++) {
        env->addPoint(center + rotate(piece[i], grid, rotation), brightness);
    }
}

