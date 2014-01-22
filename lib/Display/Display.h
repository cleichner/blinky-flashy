#define CHANNELS_PER_TLC 16

#define NUM_ROWS 12
#define NUM_COLS 8

class Display_ {
  public:
    void init();
    void show();
    void initialize_image();
    void brighten(uint16_t scale);
    void alternate(uint16_t scale);
  private:
    uint16_t image[NUM_ROWS][NUM_COLS];
};

extern Display_ Display;
