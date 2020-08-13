
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// This is one of several template application files that can be partially
// updated with tables generated from generate.c.  The inserted defines and tables
// represent how the LED strip should be logically mapped to tables and digits.

// This specific file implements a simple scoreboard a string of LEDs wrappered around 
// a holder, resulting in a 2 sided array of LEDs.  Scoring is based on volleyball
// but can be used for several other sports.  The user can enter commands
// to change the score:
//  'r' - reset scores and current side.

// that will become a scoreboard.  tester.c does some simple operations and SIMULATION
// output, via a text output of the LED table.

// To build and run, use the following:
// rm -f ./runme ; gcc tester.c -o runme ; ./runme

#define SIMULATION

#define PRINT_SCORES



/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
// GENERATED CODE BELOW


// GENERATED CODE ABOVE
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

int operation = ' ';
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
#ifdef PRINT_SCORES
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


void getOperation() {
    printf("option: ");
    operation = getchar();
}

void clearOperation() {
    getchar();
}

void usage() {
    printf("options\n");
    printf("  r - reset scores\n");
    printf("  s - side-active change\n");
    printf("  p - add to side-active score\n");
    printf("  m - subtract to side-active score\n");
}


////////////////////////////////////////////////////////////////////////////////
// setup
////////////////////////////////////////////////////////////////////////////////

void setup() {
    clearDigits();
    clearDigitLeds();
    setupDigitLeds();
}

////////////////////////////////////////////////////////////////////////////////
// loop
////////////////////////////////////////////////////////////////////////////////
void loop() {
    getOperation();
    switch (operation) {
        case 'r': scoresReset(); break;
        case 's': scoresSide();  break;
        case 'p': scoresPlus();  break;
        case 'm': scoresMinus(); break;
        case '?' :
        case 'h' : usage(); break;
    }
    clearOperation();
    setDigits();
    dumpDigits();
}

////////////////////////////////////////////////////////////////////////////////
// Main
////////////////////////////////////////////////////////////////////////////////
int main(void) {
    setup();
    while (1) {
        loop();
    }
    return 0;
}
