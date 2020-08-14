
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// This template application can be used for designing a power consumption test/.ino
// for the Arduino.
// From experience, the standard Arduino UNO board cannot support full power on all
// the LEDs of a WS2812B strip.  Instead of guessing, this application will let you
// design experiments to test various levels and RGB combinations, then port them
// to an actual Arduino .ino file.
//
// The basic idea is to display the worst case score (88 88 88 88) and periodically
// increase the RGB levels, printing out the values etc. for each step.  At some point
// the power draw will be so great, it will force a rest of the Arduino.  Not the
// most elegant method, but avoids alot of electrical theory and math.
//
// This specific to the scoreboard functionality, but could be modified for other
// types of functionality.


// To build and run, use the following:
// rm -f ./runme ; gcc power.c -o runme ; ./runme

#define SIMULATION


// NOTE: can only use one of R,G,B for now, assume R
#define LED_LEVELR_MIN 1
#define LED_LEVELG_MIN 1
#define LED_LEVELB_MIN 1

#define LED_LEVELR_MAX 255
#define LED_LEVELG_MAX 255
#define LED_LEVELB_MAX 255

#define LED_LEVELR_DELTA 1
#define LED_LEVELG_DELTA 1
#define LED_LEVELB_DELTA 1

#define LED_ADJUST_PERIOD 1

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

int ledR = 0;
int ledG = 0;
int ledB = 0;

int side1 = 1;
int score1 = 0;
int score2 = 0;

void dumpTableOnly(int table[ROWS][COLS]) {
    int col, row, val;

    for (row = 0; row < ROWS; row++) {
        for (col = 0; col < COLS; col++) {
            if (col == COLS/2) printf("     ");
            val = table[row][col];
            if (val) {
                printf("%3d ", table[row][col]);
            } else {
                printf("%3s ", " ");              
            }
        }
        if ((row+1) < ROWS) printf("\n");
   }
    printf("\n");
}

void dumpLedLevels() {
  printf("R,G,B: %d, %d, %d\n", ledR, ledG, ledB);
}

void updateLed(int position, int value) {
#ifdef ARDUINO
    int R, G, B;
    R = (value ? LED_LEVELR : 0);
    G = (value ? LED_LEVELG : 0);
    B = (value ? LED_LEVELB : 0);
    leds[position] = CRGB(R, G, B);
    FastLED.show();
#endif

    if (value) value = ledR;

#ifdef SIMULATION
    int row, col;
    for (row=0; row < ROWS; row++) {
        for (col=0; col < COLS; col++) {
            if (position == ledTable[row][col]) {
                ledTableValues[row][col] = value;
                break;
            }     
        }
    }
#endif // SIMULATION
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
#ifdef SIMULATION
    printf("%s %02d  %02d %s\n", 
    (side1 ? ">" : " "),
    score1,
    score2,
    (side1 ? " " : "<")
    );
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


////////////////////////////////////////////////////////////////////////////////
// Main
////////////////////////////////////////////////////////////////////////////////
int main(void) {
    int level;

    scoresReset();
    score1 = 88;
    score2 = 88;
    updateScores();

    for (level=LED_LEVELR_MIN; level <= LED_LEVELR_MAX; level++) {
      dumpLedLevels();
      ledR = level;
      updateScores();
      dumpTableOnly(ledTableValues);
      sleep(LED_ADJUST_PERIOD);

    }
}

