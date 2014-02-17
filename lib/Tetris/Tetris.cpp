#include "Display.h"
#include "Tetris.h"

#include <stdint.h>

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

