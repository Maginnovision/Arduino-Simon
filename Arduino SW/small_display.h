#ifndef SIMON_DISPLAY
#define SIMON_DISPLAY
#include "Adafruit_SSD1306.h"

//Create display with Adafruit_SSD1306 display(I2Cclockpin, I2Cdatapin);
//use this to "start" display display.begin();

/*
  display() draws image to screen
  clearDisplay() clears screen(sends all 0's)
  setTextSize(size) sets text size
  setTextColor(WHITE) is required. Black draws nothing White draws something
  setCursor(x, y) allows you to set cursor position
  write(char) draws a char at current cursor position
  fillScreen(uint16_t color) fills screen
  invertDisplay(bool) inverts display

  drawPixel(int16_t x, int16_t y, uint16_t color) draws a single pixel at x, y
  drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) Draws a line from x0,y0 to x1,y1
  drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) Draws a set of pixels from x,y for h pixels
  drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) Draws a set of pixels from x,y for w pixels
  drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) Draws a rectangle with bottom left being at x,y
  fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) Same as above but fills
  drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) Draws a circle with center at x0,y0
  fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) Same as above but fills
  drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
  int16_t x2, int16_t y2, uint16_t color) Draws a triangle
  fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
  int16_t x2, int16_t y2, uint16_t color) Same as above but fills
  drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
  int16_t radius, uint16_t color) Same as rect but rounded corners of radius
  fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
  int16_t radius, uint16_t color) Same as above but fills
  drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap,
  int16_t w, int16_t h, uint16_t color) Draws a Bitmap with bottom left at x,y
  drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color,
  uint16_t bg, uint8_t size) Draws a single character at x/y
  setRotation(uint8_t r) Sets display rotation */

#endif
