// for NeoPixel FeatherWing
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(
  NEOPIXEL_ROWS * NEOPIXEL_COLS,
  NEOPIXEL_PIN,
  NEO_GRB + NEO_KHZ800
);

void pixelsInit(void) {
  pixels.begin();
  pixelsClearDisplay();
}

uint32_t pixelsColour(byte red, byte green, byte blue) {
  return pixels.Color(red, green, blue);
}

void pixelsFillAll(uint32_t colour) {
  for(int y = 0; y < NEOPIXEL_ROWS; y++) {
    for(int x = 0; x < NEOPIXEL_COLS; x++) {
      pixels.setPixelColor(xy_to_pixel(x, y), colour);
    }
  }
  pixels.show();
}

void pixelsError(uint32_t colour) {
  pixelsFillAll(pixels.Color(0, 0, 0));
  pixels.setPixelColor(xy_to_pixel(0, 0), colour);
  pixels.setPixelColor(xy_to_pixel(7, 0), colour);
  pixels.setPixelColor(xy_to_pixel(0, 3), colour);
  pixels.setPixelColor(xy_to_pixel(7, 3), colour);
  pixels.show();
}

void pixelsErrorFlash(uint32_t colour) {
  byte i;
  for(i=0; i<10; i++) {
    pixelsClearDisplay();
    delay(250);
    pixelsError(colour);
    delay(250);
  }
}

void pixelsClearDisplay(void) {
    pixelsFillAll(0);
}

void pixelsCheckerboard(uint32_t colour, byte order) {
  for(int y = 0; y < NEOPIXEL_ROWS; y++) {
    for(int x = 0; x < NEOPIXEL_COLS; x++) {
      if(order == 0) {
        if((y % 2 == 0 && x % 2 == 0) || (y % 2 != 0 && x % 2 != 0)) {
          pixels.setPixelColor(xy_to_pixel(x, y), colour);
        } else {
          pixels.setPixelColor(xy_to_pixel(x, y), pixels.Color(0, 0, 0));
        }
      } else {
        if((y % 2 == 0 && x % 2 != 0) || (y % 2 != 0 && x % 2 == 0)) {
          pixels.setPixelColor(xy_to_pixel(x, y), colour);
        } else {
          pixels.setPixelColor(xy_to_pixel(x, y), pixels.Color(0, 0, 0));
        }
      }
    }
  }
  pixels.show();
}

void pixelsAnimateCheckerboard(uint32_t colour, int interframe_delay, byte secs) {
  for(byte frame=0; frame<secs*1000 / interframe_delay; frame++) {
    pixelsCheckerboard(colour, (frame % 2 == 0 ? 0 : 1));
    delay(interframe_delay);
  }
}
