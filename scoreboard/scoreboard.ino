#include <FastLED.h>

// This is one of several template application files that can be partially
// updated with tables generated from generate.c.  The inserted defines and tables
// represent how the LED strip should be logically mapped to tables and digits.

// This specific file implements a simple scoreboard a string of LEDs wrappered around 
// a holder, resulting in a 2 sided array of LEDs.  Scoring is based on volleyball
// but can be used for several other sports.  The user can severa buttons
// to change the score:
//  TBD - reset scores
//  TBD - side-active change
//  TBD - add to side-active score
//  TBD - subtract to side-active score

// use the following to debug with Serial port
#define DEBUG
//#define SIMULATION

#define LED_LEVELR_MIN 0
#define LED_LEVELG_MIN 1
#define LED_LEVELB_MIN 0

#define LED_LEVELR_MAX 0
#define LED_LEVELG_MAX 100
#define LED_LEVELB_MAX 0

#define LED_LEVELR 1
#define LED_LEVELG 1
#define LED_LEVELB 1

#define LED_PIN  7
#define NUM_LEDS 150

// Define the array of leds
CRGB leds[NUM_LEDS];

#ifdef DEBUG
char printbuffer[120];
#endif

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
// GENERATED CODE BELOW

// This following tables and defines were generated based on given inputs
// reflected in the defines section.  Assuming the LED strip is a WS2812B
// LED strip with 150 addressable LEDs, these will be 33.33 mm apart:
// 
//  |---------o---o   ...   o---o---------|  150 count
//            <- - - - - - - - ->
//              5000 mm
//              16.4 ft
//            <-->
//             33.3 mm
//   <- - - ->
//     ~150mm
//
// When wrapped around a frame 'ROWS' times, with 'COLS' LEDs per row (double side)
// the frame needs to be approx. 
// With ROWS = 5 and COLS = 30
// H = ROWS * 33.3 mm = 166.50mm = 6.56 in
// W = COLS/2 * 33.3mm - Thickness
//   assume Thickness at 5mm (leaves some slack) then
// W = COLS/2 * 33.3mm - 5mm = 494.50mm = 19.47 in

#define TOP_RIGHT   1
#define START_LED   0
#define COLS        30
#define ROWS        5
#define SIDES       2
#define DIGIT_WIDTH 3
#define DIGIT_GAP   0
#define SCORE_GAP   3
#define MAX_SCORE   99
#define DIGITA      0
#define DIGITB      1
#define DIGITC      2
#define DIGITD      3
#define DIGITE      4
#define DIGITF      5
#define DIGITG      6
#define DIGITH      7
#define DIGITS      8
// This table is used to inspect how the led string is layed out as digits
#ifdef SIMULATION
int ledTable[ROWS][COLS] = {
  {  0,  1,  2,  3,  4,  5, -1, -1, -1,  9, 10, 11, 12, 13, 14,      15, 16, 17, 18, 19, 20, -1, -1, -1, 24, 25, 26, 27, 28, 29},
  { 30, 31, 32, 33, 34, 35, -1, -1, -1, 39, 40, 41, 42, 43, 44,      45, 46, 47, 48, 49, 50, -1, -1, -1, 54, 55, 56, 57, 58, 59},
  { 60, 61, 62, 63, 64, 65, -1, -1, -1, 69, 70, 71, 72, 73, 74,      75, 76, 77, 78, 79, 80, -1, -1, -1, 84, 85, 86, 87, 88, 89},
  { 90, 91, 92, 93, 94, 95, -1, -1, -1, 99,100,101,102,103,104,     105,106,107,108,109,110, -1, -1, -1,114,115,116,117,118,119},
  {120,121,122,123,124,125, -1, -1, -1,129,130,131,132,133,134,     135,136,137,138,139,140, -1, -1, -1,144,145,146,147,148,149}
};
#endif // SIMULATION
// This table is used display the simulated led table
#ifdef SIMULATION
int ledTableValues[ROWS][COLS] = {
  {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}
};
#endif // SIMULATION
// This table is a map of digits to leds
//   side1 -  side2  
//   00 00 -  00 00  
//   AB CD -  EF GH  
int ledDigitsArray[DIGITS][ROWS][DIGIT_WIDTH] = {
{
  {  0,  1,  2 },
  { 30, 31, 32 },
  { 60, 61, 62 },
  { 90, 91, 92 },
  {120,121,122 }
},
{
  {  3,  4,  5 },
  { 33, 34, 35 },
  { 63, 64, 65 },
  { 93, 94, 95 },
  {123,124,125 }
},
{
  {  9, 10, 11 },
  { 39, 40, 41 },
  { 69, 70, 71 },
  { 99,100,101 },
  {129,130,131 }
},
{
  { 12, 13, 14 },
  { 42, 43, 44 },
  { 72, 73, 74 },
  {102,103,104 },
  {132,133,134 }
},
{
  { 15, 16, 17 },
  { 45, 46, 47 },
  { 75, 76, 77 },
  {105,106,107 },
  {135,136,137 }
},
{
  { 18, 19, 20 },
  { 48, 49, 50 },
  { 78, 79, 80 },
  {108,109,110 },
  {138,139,140 }
},
{
  { 24, 25, 26 },
  { 54, 55, 56 },
  { 84, 85, 86 },
  {114,115,116 },
  {144,145,146 }
},
{
  { 27, 28, 29 },
  { 57, 58, 59 },
  { 87, 88, 89 },
  {117,118,119 },
  {147,148,149 }
},
};
// This table is a map of nibbles (0-9) to digits, specifically which leds are on/off
int numArrays[10][ROWS][DIGIT_WIDTH] = {
{
  {  1,  1,  1 },
  {  1,  0,  1 },
  {  1,  0,  1 },
  {  1,  0,  1 },
  {  1,  1,  1 }
},
{
  {  0,  0,  1 },
  {  0,  0,  1 },
  {  0,  0,  1 },
  {  0,  0,  1 },
  {  0,  0,  1 }
},
{
  {  1,  1,  1 },
  {  0,  0,  1 },
  {  1,  1,  1 },
  {  1,  0,  0 },
  {  1,  1,  1 }
},
{
  {  1,  1,  1 },
  {  0,  0,  1 },
  {  1,  1,  1 },
  {  0,  0,  1 },
  {  1,  1,  1 }
},
{
  {  1,  0,  1 },
  {  1,  0,  1 },
  {  1,  1,  1 },
  {  0,  0,  1 },
  {  0,  0,  1 }
},
{
  {  1,  1,  1 },
  {  1,  0,  0 },
  {  1,  1,  1 },
  {  0,  0,  1 },
  {  1,  1,  1 }
},
{
  {  1,  1,  1 },
  {  1,  0,  0 },
  {  1,  1,  1 },
  {  1,  0,  1 },
  {  1,  1,  1 }
},
{
  {  1,  1,  1 },
  {  0,  0,  1 },
  {  0,  0,  1 },
  {  0,  0,  1 },
  {  0,  0,  1 }
},
{
  {  1,  1,  1 },
  {  1,  0,  1 },
  {  1,  1,  1 },
  {  1,  0,  1 },
  {  1,  1,  1 }
},
{
  {  1,  1,  1 },
  {  1,  0,  1 },
  {  1,  1,  1 },
  {  0,  0,  1 },
  {  1,  1,  1 }
},
};

// GENERATED CODE ABOVE
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

#define BUTTON_PLUS  0
#define BUTTON_MINUS 1
#define BUTTON_SIDE  2
const int commonPin = 2;
const int buttonPins[] = {3,4,5};
unsigned long lastFire = 0;

int ledR = LED_LEVELR;
int ledG = LED_LEVELG;
int ledB = LED_LEVELB;

int operation = ' ';
int side1 = 1;
int score1 = 0;
int score2 = 0;

void updateLed(int position, int value) {
    int R, G, B;
    R = (value ? ledR : 0);
    G = (value ? ledG : 0);
    B = (value ? ledB : 0);
    leds[position] = CRGB(R, G, B);
    FastLED.show();
}

void clearAllLeds() {
  int i;

  for (i=0; i<NUM_LEDS; i++) {
    updateLed(i, 0);
  }
}

void updateDigit(int digitNum, int nibble) {
    // get pointer to numArrays from nibble, numPtr
    // get pointer to digitN from digit num, digPtr 
    // for each row/col call updateLed(*digPtr, *numPtr)
    int row, col, led, val;

    for (row = 0; row < ROWS; row++) {
        for (col = 0; col < DIGIT_WIDTH; col++) {
            led =  ledDigitsArray[digitNum][row][col];
            val =  numArrays[nibble][row][col];
            updateLed(led,val);
        }   
    }
}

void updateScores() {
#ifdef DEBUG2
    sprintf(printbuffer, "%s %02d  %02d %s\n",
    (side1 ? ">" : " "),
    score1,
    score2,
    (side1 ? " " : "<")
    );
    Serial.print(printbuffer);
#endif

    int nibble;
    nibble = score1/10;
    updateDigit(DIGITA, nibble);
    nibble = score1%10;
    updateDigit(DIGITB, nibble);
    nibble = score2/10;
    updateDigit(DIGITC, nibble);
    nibble = score2%10;
    updateDigit(DIGITD, nibble);
    nibble = score1/10;
    updateDigit(DIGITE, nibble);
    nibble = score1%10;
    updateDigit(DIGITF, nibble);
    nibble = score2/10;
    updateDigit(DIGITG, nibble);
    nibble = score2%10;
    updateDigit(DIGITH, nibble);
}

void scoresReset() {
    score1 = 0;
    score2 = 0;
    side1 = 1;
}

void scoresSide() {
    side1 = !side1;
}

void scoresPlus() {
    if (side1) { score1 += 1; }
    else       { score2 += 1; }
}

void scoresMinus() {
    if (side1) { score1 -= 1; }
    else       { score2 -= 1; }
    if (score1 < 0) { score1 = 0; }
    if (score2 < 0) { score2 = 0; }
}

void pressInterrupt() { // ISR
  if (millis() - lastFire < 400) { // Debounce
    return;
  }
  lastFire = millis();

  configureDistinct(); // Setup pins for testing individual buttons

  for (int i = 0; i < sizeof(buttonPins) / sizeof(int); i++) { // Test each button for press
    if (!digitalRead(buttonPins[i])) {
      press(i);
    }
  }

  configureCommon(); // Return to original state
}

void configureCommon() {
  pinMode(commonPin, INPUT_PULLUP);

  for (int i = 0; i < sizeof(buttonPins) / sizeof(int); i++) {
    pinMode(buttonPins[i], OUTPUT);
    digitalWrite(buttonPins[i], LOW);
  }
}

void configureDistinct() {
  pinMode(commonPin, OUTPUT);
  digitalWrite(commonPin, LOW);

  for (int i = 0; i < sizeof(buttonPins) / sizeof(int); i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}

void press(int button) { // Our handler
  switch(button) {
    case BUTTON_PLUS:  operation = 'p'; break;
    case BUTTON_MINUS: operation = 'm'; break;
    case BUTTON_SIDE:  operation = 's'; break;
  }
}


////////////////////////////////////////////////////////////////////////////////
// setup
////////////////////////////////////////////////////////////////////////////////
void setup() {
#ifdef DEBUG
    Serial.begin(9600);
#endif

    configureCommon(); // Setup pins for interrupt
    attachInterrupt(digitalPinToInterrupt(commonPin), pressInterrupt, FALLING);

    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    clearAllLeds();
    scoresReset();
    updateScores();
}

////////////////////////////////////////////////////////////////////////////////
// loop
////////////////////////////////////////////////////////////////////////////////
void loop() {
    switch (operation) {
        case 'r': scoresReset(); break;
        case 's': scoresSide();  break;
        case 'p': scoresPlus();  break;
        case 'm': scoresMinus(); break;
    }
    operation = ' ';
    updateScores();
}
