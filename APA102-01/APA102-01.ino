#include "FastLED.h"
//
#define NUM_LEDS 200
#define DATA_PIN 4
#define CLOCK_PIN 5
#define TWO_PI 6.283185307
CRGB leds[NUM_LEDS];

void setup()
{
  // put your setup code here, to run once:
  delay(200);
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN>(leds, NUM_LEDS);
}

void loop()
{
  float t = millis() * 0.04;

  // put your main code here, to run repeatedly:
  float osc1 = 0;
  float osc2 = 0;
  for (int x = 0; x < NUM_LEDS; x++)
  {
    osc1 = sinf(fmod(x * 0.11234 + t * 0.0523, TWO_PI)) * 0.5 + 0.5;
    // osc1 = powf(osc1, 2);
    osc1 *= 20;

    osc2 = sinf(fmod(x * 0.0734 + osc1 + t * 0.0312, TWO_PI)) * 0.5 + 0.5;
    osc2 = powf(osc2, 3);
    osc2 *= 255;

    float v = (osc1 + osc2) * 0.8;
    // float v = osc2;
    leds[x] = CHSV(150 + osc1 * 0.4, 250, (int)v);
  }
  FastLED.show();
  // delay(16);
}
