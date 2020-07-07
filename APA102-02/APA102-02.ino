
#include <Adafruit_DotStar.h>
#include <SPI.h>

#include "Pixel.h"

#define NUMPIXELS 200

#define DATAPIN 4
#define CLOCKPIN 5

Adafruit_DotStar leds(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BGR);

Pixel **pixels;

float rnd01;
float rnd02;
float rnd03;
float rnd04;
float rnd05;

void setup()
{

  leds.begin();
  leds.show();

  randomSeed(analogRead(0));
  rnd01 = random(TWO_PI);

  delay(10);

  randomSeed(analogRead(0));
  rnd02 = random(TWO_PI);

  delay(10);

  randomSeed(analogRead(0));
  rnd04 = random(TWO_PI);

  delay(10);

  randomSeed(analogRead(0));
  rnd03 = random(TWO_PI);

  delay(10);

  randomSeed(analogRead(0));
  rnd05 = random(TWO_PI);

  initPixels();
}

void loop()
{
  shadePixels01();
  renderPixels();
}

void initPixels()
{
  pixels = new Pixel *[NUMPIXELS];
  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixels[i] = new Pixel(i, 0, 0, 0);
    pixels[i]->hsv(i / (float)NUMPIXELS * 360.0, 1, 1);
  }
}

float step(float t, float v)
{
  return t < v ? 0 : 1;
}
float fract(float x)
{
  return x - (int)x;
}

float random(float x)
{
  return fract(sinf(fmod(x, 1)) * 1e4);
}

float randomSerie(float x, float freq, float t)
{
  return step(.8, random(floorf(x * freq) - floorf(t)));
}

void renderPixels()
{
  Pixel *pixel;
  int ir, ig, ib;

  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixel = pixels[i];

    ir = (int)(pixel->fr * 10.0);
    ig = (int)(pixel->fg * 10.0);
    ib = (int)(pixel->fb * 10.0);

    leds.setPixelColor(i, ir, ig, ib);
  }

  leds.show();
}

void shadePixels01()
{
  float t = micros() * 0.000005;
  float osc1;
  float osc2;
  float osc3;
  float osc4;
  float osc5;
  for (int i = 0; i < NUMPIXELS; i++)
  {
    osc3 = sinf(fmod(rnd03 + t * 0.0005123 + i * 0.004532, TWO_PI)) * 0.633 + 0.9123;
    osc4 = sinf(fmod(rnd04 + t * 0.0001234 + i * 0.003212 + osc3 * 2.324, TWO_PI)) * 0.5 + .821234;
    osc5 = sinf(fmod(rnd05 + t * 0.0001523 + i * 0.001212 + osc4 * 8.123, TWO_PI)) * 0.3 + 0.75;

    osc1 = sinf(fmod(rnd01 + t + osc3 + i * 0.467 * osc4, TWO_PI)) * 0.5 + 0.5;
    osc1 = osc1 * osc1 * osc1;

    osc2 = sinf(fmod(rnd02 + t * 0.1423 + i * 0.02443, TWO_PI)) * 0.5 + 0.5;
    osc2 = osc2 * osc2 * osc2;

    pixels[i]->hsv(fmod(osc2 * 100.0 - 40, 360), osc5 * 0.5 + 0.5, osc1);
  }
}

void shadePixels02()
{
  float u_time = micros() * 0.000001;
  float rnd01;

  for (int i = 0; i < NUMPIXELS; i++)
  {
    float freq = random(floorf(u_time)) + abs(atanf(u_time) * 0.1);
    float t = 60.0f + u_time * (1.0f - freq) * 30.0f;

    rnd01 = randomSerie(i * 0.01, freq * 10.f, t);
    pixels[i]->hsv(0, 1, rnd01);
  }
}
