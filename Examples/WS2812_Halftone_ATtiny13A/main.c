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
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "light_ws2812.h"
#include "font5x3.h"

#define WIDTH          12 // actual width = WIDTH * 2 = 24
#define HEIGHT         5
#define BITMAP_SIZE    (((WIDTH * HEIGHT) + 7) / 8)
#define CHAR_GAP       1 // space for each character
#define SCORLL_DELAY   100 // ms

// please also config ws2812_config.h

int8_t offset = WIDTH; // right most position
uint8_t bitmap[BITMAP_SIZE]; // ATtiny13A only have space to store mono

char msg[] = "ARE YOU READY?";

void clearBitmap() {
	uint8_t idx = BITMAP_SIZE;
	while (idx--) {
		bitmap[idx] = 0;
	}
}

void setPixel(uint16_t i) {
	uint8_t idx = (uint8_t)i / 8;
	uint8_t bit_offset = (uint8_t)i % 8;
	uint8_t bit_mask = 0b10000000 >> bit_offset;
	bitmap[idx] |= bit_mask;
}

void write_char(int8_t pos, uint8_t c) {
  uint8_t data_offset = (c - 32) * (((FONT_WIDTH * FONT_HEIGHT) + 7) / 8);
  uint8_t cur_bit = 0;
  uint8_t data = 0;
  uint16_t i = 0;
  uint16_t j = 0;

  for (j = 0; j < (FONT_WIDTH * FONT_HEIGHT); j++) {
    if (!cur_bit) {
      data = pgm_read_byte(&font_data[data_offset++]);
      cur_bit = 0b10000000;
    }
    int8_t col = pos + (int8_t)(j / FONT_HEIGHT);
    if ((col >= 0) && (col < WIDTH)) {
      uint8_t row = j % FONT_HEIGHT;
      if (row % 2) {
        i = ((row + 1) * WIDTH) - col - 1;
      } else {
        i = (row * WIDTH) + col;
      }

      if (data & cur_bit) {
        setPixel(i);
      }
    }
    cur_bit >>= 1;
  }
}

// Since 64 Bytes cannot store full color bitmap buffer,
// so use this function determine each pixel color on the fly.
// This function will call in the middle while sending data to WS2812.
// This function must not run over 50 us or it will treat as another data cycle,
// so keep it as simply as possible
// Fail syndrome: only first LED blink
uint8_t getPixelColorFunction(uint8_t idx, uint8_t bit_mask, uint8_t brg_idx) {
	if (bitmap[idx] & bit_mask) { // check LED should on or off
		switch(brg_idx) {
			case 0: // Blue
				return ((bit_mask >> 2) & 0b00001111) + idx;
			case 1: // Red
				return ((bit_mask >> 5) & 0b00001111) + BITMAP_SIZE - idx - 1;
			default: //2: Green
				return (bit_mask & 0b00011111);
		}
	} else { // LED off
		return 0;
	}
}

int main(void)
{
  // init pin
  DDRB |= _BV(ws2812_pin); // ws2812_config.h

  // loop
  while (1)
  {
	clearBitmap();

	uint8_t i = 0;
	for (; i < (sizeof(msg) - 1); i++) {
		write_char(offset + (i * (FONT_WIDTH + CHAR_GAP)), msg[i]);
	}

    offset--;
    if (offset < (-(FONT_WIDTH + CHAR_GAP) * (int8_t)sizeof(msg))) { // left most position
		offset = WIDTH; // return to right most position
    }

    ws2812_set_leds_func_ptr(WIDTH * HEIGHT, getPixelColorFunction);

    _delay_ms(SCORLL_DELAY);
  }
}
