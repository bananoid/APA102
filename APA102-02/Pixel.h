#include "Arduino.h"

#ifndef PIXEL_H
#define PIXEL_H

typedef struct
{
  uint8_t r;
  uint8_t g;
  uint8_t b;
} RGB;

typedef struct
{
  uint8_t h;
  uint8_t s;
  uint8_t v;
} HSV;

typedef struct
{
  float r;
  float g;
  float b;
} fRGB;

typedef struct
{
  fRGB a;
  fRGB b;
  fRGB c;
  fRGB d;
} Palette;

class Pixel
{
private:
public:
  int inx;

  float fr;
  float fg;
  float fb;

  Pixel(int inx, float r, float g, float b);

  static RGB HSVtoRGB(uint8_t H, uint8_t S, uint8_t V);
  static fRGB cosinePalette(float t, fRGB a, fRGB b, fRGB c, fRGB d);

  void hsv(int H, float S, float V);
};

#endif