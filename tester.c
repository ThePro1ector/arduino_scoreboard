
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// This is the first of several template application files that can be partially
// updated with tables generated from generate.c.  The inserted defines and tables
// represent how the LED strip should be logically mapped to tables and digits.

// This specific file allows quick testing of the scoreboard functionality using
// a string of LEDs wrappered around a holder, resulting in a 2 sided array of LEDs
// that will become a scoreboard.  tester.c does some simple operations and simulated
// output, via a text output of the LED table.

// To build and run, use the following:
// rm -f ./runme ; gcc tester.c -o runme ; ./runme

// TODO change to variables for sides
#define LED_LEVELR 1
#define LED_LEVELG 1
#define LED_LEVELB 1

/////////////////////////////////////////////////////////////////
// GENERATED CODE BELOW

this will get replaces

// GENERATED CODE ABOVE
/////////////////////////////////////////////////////////////////

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


void updateLed(int position, int value) {
    int R, G, B;
    R = (value ? LED_LEVELR : 0);
    G = (value ? LED_LEVELG : 0);
    B = (value ? LED_LEVELB : 0);
#ifdef ARDUINO
    leds[position] = CRGB(R, G, B);
    FastLED.show();
#endif

#ifdef SIMULATED
    int row, col;
    for (row=0; row < ROWS; row++) {
        for (col=0; col < COLS; col++) {
            if (position == ledTable[row][col]) {
                ledTableValues[row][col] = value;
                break;
            }     
        }
    }
#endif // SIMULATED
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
#ifdef SIMULATED
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
    else       { score1 -= 1; }
    if (score1 < 0) { score1 = 0; }
    if (score2 < 0) { score2 = 0; }
}


////////////////////////////////////////////////////////////////////////////////
// Main
////////////////////////////////////////////////////////////////////////////////
int main(void) {
    int i;

    printLedArrays();
    printNumArrays();

    // start reset
    scoresReset();
    updateScores();
    dumpTableOnly(ledTableValues);

    // expect > 01  00
    scoresPlus();
    updateScores();
    dumpTableOnly(ledTableValues);

    // expect > 02  00
    scoresPlus();
    updateScores();
    dumpTableOnly(ledTableValues);

    // change side
    scoresSide();

    // expect   02  01 <
    scoresPlus();
    updateScores();
    dumpTableOnly(ledTableValues);

    // expect   02  02 <
    scoresPlus();
    updateScores();
    dumpTableOnly(ledTableValues);

    // expect   02  01 <
    scoresMinus();
    updateScores();
    dumpTableOnly(ledTableValues);

    // test reset
    // expect > 00  00 
    scoresReset();
    updateScores();
    dumpTableOnly(ledTableValues);

    // expect  > 15  00
    for (i=0; i<15; i++) scoresPlus();
    updateScores();
    dumpTableOnly(ledTableValues);

    // expect    15  23 <
    scoresSide();
    for (i=0; i<21; i++) scoresPlus();
    updateScores();
    dumpTableOnly(ledTableValues);

}

