#include <FastLED.h>

#define DATA_PIN    2
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    300

CRGB leds[NUM_LEDS];
byte GREEN;
byte BLUE;
byte RED;

#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120

void setup() {
  delay(3000);
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  EVERY_N_MILLISECONDS( 20 ) { fastwaves(); }
}

void fastwaves() {
  leds[0].b = beatsin8(30);
  leds[0].g = beatsin8(40);
  leds[0].r = beatsin8(50);
  memmove(leds+1, leds, (NUM_LEDS-1)*3);
  FastLED.show();
}
  


