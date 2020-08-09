
#include <FastLED.h>

#define LED_PIN     7
#define NUM_LEDS    150
CRGB leds[NUM_LEDS];


void get_op() {
    //TBD - get from buttons
}

void clr_op() {
    // NOOP
}


void setup() {
    
    leds[0] = CRGB(255, 0, 0);
    FastLED.show();
}

void loop() {

}
