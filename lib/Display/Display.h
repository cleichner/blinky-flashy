#define NUM_ROWS 12
#define NUM_COLS 8

typedef enum {
   VERTICAL,
   HORIZONTAL,
} orientation_t;

class DisplayCls {
  public:
    void init();
    void show();
    void clear();
    void checkerboard(uint16_t intensity, bool offset);
    void alternate(uint16_t intensity);
    void line(uint8_t index, orientation_t orientation,  uint16_t intensity);
    void line(uint8_t row, uint8_t col, uint8_t length,
              orientation_t orientation, uint16_t intensity);
  private:
    uint16_t image[NUM_ROWS][NUM_COLS];
};

extern DisplayCls Display;
