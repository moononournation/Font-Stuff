/*
  https://github.com/moononournation/Font-Stuff
  Reference:
  ASCII characters from 32 to 128:
  !"#$%&'()*+,-./
  0123456789
  :;<=>?@
  ABCDEFGHIJKLMNOPQRSTUVWXYZ
  [\]^_`
  abcdefghijklmnopqrstuvwxyz
  {|}~
*/
#include "font5x3.h"
#include "WS2811.h"

#define WIDTH          12 // actual width = WIDTH * 2 = 24
#define HEIGHT         5
#define CHAR_GAP       1 // space for each character
#define SCORLL_DELAY    200 // ms

// DigiSpark WS2811 Library config
#define PIN            6
DEFINE_WS2811_FN(WS2811RGB, PORTB, PIN)

int8_t offset = WIDTH; // right most position
RGB_t rgb[WIDTH * HEIGHT];

char msg[] = "HELLO WORLD!";

void setup() {
  // init pin
  pinMode(PIN, OUTPUT);
}

void loop() {
  for (uint8_t i = 0; i < sizeof(msg) - 1; i++) {
    write_char(offset + (i * FONT_WIDTH + CHAR_GAP), msg[i]);
  }

  WS2811RGB(rgb, ARRAYLEN(rgb));

  offset--;
  if (offset < (-(FONT_WIDTH + CHAR_GAP) * (int8_t)sizeof(msg))) { // left most position
    offset = WIDTH; // return to right most position
  }

  delay(SCORLL_DELAY);
}

void write_char(int8_t pos, uint8_t c) {
  uint8_t data_offset = (c - 32) * (((FONT_WIDTH * FONT_HEIGHT) + 7) / 8);
  uint8_t bit_offset = 7;
  uint8_t data = 0;
  uint8_t i = 0;

  for (uint8_t j = 0; j < (FONT_WIDTH * FONT_HEIGHT); j++) {
    if (bit_offset == 7) {
      data = pgm_read_byte(&font_data[data_offset]);
      data_offset++;
      bit_offset = 0;
    } else {
      bit_offset++;
    }
    int8_t col = pos + (j / FONT_HEIGHT);
    if ((col >= 0) && (col < WIDTH)) {
      uint8_t row = j % FONT_HEIGHT;
      if (row % 2) {
        i = ((row + 1) * WIDTH) - col - 1;
      } else {
        i = (row * WIDTH) + col;
      }

      if (data & (0b10000000 >> bit_offset)) {
        setPixel(i, col / 2, row, (WIDTH - col) / 2); // customize color
      } else {
        setPixel(i, 0, 0, 0);
      }
    }
  }
}

void setPixel(uint8_t i, uint8_t r, uint8_t g, uint8_t b) {
  rgb[i].r = r;
  rgb[i].g = g;
  rgb[i].b = b;
}

