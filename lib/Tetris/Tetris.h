#ifndef TETRIS_H
#define TETRIS_H

#define SQUARES_IN_PIECE 4

typedef enum {
    THREE_GRID = 0,
    FOUR_GRID = 1,
} RotationGrid;

#include <stdint.h>

class Point {
  public:
    int8_t x;
    int8_t y;
    Point() : x(0), y(0) {}
    Point(int8_t x, int8_t y) : x(x), y(y) { }
    inline Point operator +(const Point& p) const {
        return Point(x + p.x, y + p.y);
    }
};

class TetrisPiece {
  private:
    Point piece[SQUARES_IN_PIECE];
    RotationGrid grid;
    uint16_t brightness;
  public:
    TetrisPiece(Point piece[SQUARES_IN_PIECE], RotationGrid grid, uint16_t brightness) :
        grid(grid), brightness(brightness) {
        for (int8_t i = 0; i < SQUARES_IN_PIECE; i++) {
            this->piece[i] = piece[i];
        }
    }
    void show(DisplayCls* d, const Point& center, int8_t rotation);
};

Point rotate(Point p, int8_t size, int8_t n);

void showPiece(Point piece[SQUARES_IN_PIECE], int8_t size, DisplayCls* d,
               const Point& center, int8_t rotation, uint16_t brightness);

#endif // TETRIS_H
