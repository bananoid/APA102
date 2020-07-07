#include "Pixel.h"
#include <Arduino.h>

Pixel::Pixel(int inx, float r, float g, float b)
{
  this->inx = inx;

  this->fr = r;
  this->fg = g;
  this->fb = b;
}

void Pixel::hsv(int H, float S, float V)
{
  float C = S * V;
  float X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
  float m = V - C;
  float Rs, Gs, Bs;

  if (H >= 0 && H < 60)
  {
    Rs = C;
    Gs = X;
    Bs = 0;
  }
  else if (H >= 60 && H < 120)
  {
    Rs = X;
    Gs = C;
    Bs = 0;
  }
  else if (H >= 120 && H < 180)
  {
    Rs = 0;
    Gs = C;
    Bs = X;
  }
  else if (H >= 180 && H < 240)
  {
    Rs = 0;
    Gs = X;
    Bs = C;
  }
  else if (H >= 240 && H < 300)
  {
    Rs = X;
    Gs = 0;
    Bs = C;
  }
  else
  {
    Rs = C;
    Gs = 0;
    Bs = X;
  }

  this->fr = (Rs + m);
  this->fg = (Gs + m);
  this->fb = (Bs + m);
}

RGB Pixel::HSVtoRGB(uint8_t H, uint8_t S, uint8_t V)
{
  RGB returncolor;
  uint16_t p, q, t, i, f, h, s, v;
  h = H;
  s = S;
  v = V;
  if (s == 0)
  {
    returncolor.r = returncolor.g = returncolor.b = v;
  }
  else
  {
    h = h << 4;
    i = h / 680;
    f = (h % 680) >> 4;
    p = (v * (255 - s)) >> 8;
    q = (v * ((10710 - (s * f)) / 42)) >> 8;
    t = (v * ((10710 - (s * (42 - f))) / 42)) >> 8;

    switch (i)
    {
    case 1:
      returncolor.r = q;
      returncolor.g = v;
      returncolor.b = p;
      break;
    case 2:
      returncolor.r = p;
      returncolor.g = v;
      returncolor.b = t;
      break;
    case 3:
      returncolor.r = p;
      returncolor.g = q;
      returncolor.b = v;
      break;
    case 4:
      returncolor.r = t;
      returncolor.g = p;
      returncolor.b = v;
      break;
    case 5:
      returncolor.r = v;
      returncolor.g = p;
      returncolor.b = q;
      break;
    default: //in case i > 5 or i == 0
      returncolor.r = v;
      returncolor.g = t;
      returncolor.b = p;
      break;
    }
  }

  return returncolor;
}

fRGB Pixel::cosinePalette(float t, fRGB a, fRGB b, fRGB c, fRGB d)
{
  fRGB color;

  color.r = a.r + b.r * cosf(TWO_PI * (c.r * t + d.r));
  color.g = a.g + b.g * cosf(TWO_PI * (c.g * t + d.g));
  color.b = a.b + b.b * cosf(TWO_PI * (c.b * t + d.b));

  return color;
}
