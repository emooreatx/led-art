#include <FastLED.h>

#define DATA_PIN    2
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    300
#define NUMSPARKS   5
#define SPARKLIFE   1
#define JAZZHANDS 1

CRGB leds[NUM_LEDS];
byte GREEN;
byte BLUE;
byte RED;
int LEADLED = 0;
CRGB SPARKVALS[NUMSPARKS];
CRGB SPARKADDS[NUMSPARKS];


#define BRIGHTNESS          255
#define FRAMES_PER_SECOND  120

void setup() {
  delay(3000);
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  movingdot(); 
}

void justthewave() {
  leds[0].b = beatsin8(100);
  leds[0].g = beatsin8(75);
  leds[0].r = beatsin8(66);
  memmove(leds+1, leds, (NUM_LEDS-1)*3);
  FastLED.show();
}

void movingdot() {
  if (LEADLED > 30) {
    for (int i = 0; i < NUMSPARKS; i = i+1) {
      leds[SPARKADDS[i]] = SPARKVALS[i];
    }
  }
  leds[LEADLED].b = beatsin8(100, 50, 255);
  leds[LEADLED].g = beatsin8(78, 0, 255);
  leds[LEADLED].r = beatsin8(66, 0, 150);
  fadeToBlackBy(leds, NUM_LEDS, 1);
  if (LEADLED++ >= 299) {
    LEADLED = 0; 
  }

  FastLED.show();
}

  
