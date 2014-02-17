#define NUM_ROWS 12
#define NUM_COLS 8

class DisplayCls {
  public:
    void init();
    void show();
    inline void point(uint8_t x, uint8_t y, uint16_t brightness);
    void clear();
  private:
    uint16_t image[NUM_ROWS][NUM_COLS];
};

inline void DisplayCls::point(uint8_t x, uint8_t y, uint16_t brightness) {
    image[y][x] = brightness;
}

extern DisplayCls Display;
