
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// gcc scoreboard.c -o runme ; ./runme

// C version to test ideas faster without loading on Arduino


#define SIMULATION
#define SCORE_PRINT
#define TEST_SEQUENCE


#define TOP_RIGHT 0
#define COLS (2*15)
#define ROWS 5
#define SIDES 2
#define DIGIT_WIDTH 3
#define DIGIT_GAP 0
#define SCORE_GAP 3

#if SIDES == 1
#define DIGITA  0
#define DIGITB  1
#define DIGITC  2
#define DIGITD  3
#define DIGITS  4
#endif
#if SIDES == 2
#define DIGITA  0
#define DIGITB  1
#define DIGITC  2
#define DIGITD  3
#define DIGITE  4
#define DIGITF  5
#define DIGITG  6
#define DIGITH  7
#define DIGITS  8
#endif




int operation = ' ';
bool sideA = true;
int scoreA = 0;
int scoreB = 0;


int digitLeds[DIGITS][ROWS][DIGIT_WIDTH];

// TODO really should test by setting led in expected position and translating that to a simulated set 
// of 'wrapped' leds
// remove this
int digits[DIGITS][ROWS][DIGIT_WIDTH];
// use 
// int ledStrip[ROWS*COLS];
// void dumpLedStripAsTable() {
//     int row, col, index;

//     for (row = 0; row < ROWS; row ++) {
//         for (col = 0; col < COLS; col ++) {
            
//         }
//         printf("\n");
//     }
// }




void usage() {
    printf("options\n");
    printf("  r - reset scores\n");
    printf("  s - side-active change\n");
    printf("  p - add to side-active score\n");
    printf("  m - subtract to side-active score\n");
}

int ledStripAsTable[5][22] = {
  {  40,  41,  42,  43,  -1,  -1,  -1,  47,  48,  49,  50,       51,  52,  53,  54,  -1,  -1,  -1,  58,  59,  60,  61 },
  {  62,  63,  64,  65,  -1,  -1,  -1,  69,  70,  71,  72,       73,  74,  75,  76,  -1,  -1,  -1,  80,  81,  82,  83 },
  {  84,  85,  86,  87,  -1,  -1,  -1,  91,  92,  93,  94,       95,  96,  97,  98,  -1,  -1,  -1, 102, 103, 104, 105 },
  { 106, 107, 108, 109,  -1,  -1,  -1, 113, 114, 115, 116,      117, 118, 119, 120,  -1,  -1,  -1, 124, 125, 126, 127 },
  { 128, 129, 130, 131,  -1,  -1,  -1, 135, 136, 137, 138,      139, 140, 141, 142,  -1,  -1,  -1, 146, 147, 148, 149 }
};
int ledStripAsTableValues[5][22] = {
  {   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0  },
  {   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0  },
  {   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0  },
  {   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0  },
  {   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0  }
};
void dumpLedStripAsTableValues() {
    int col, row;
    for (row = 0; row < ROWS; row++) {
        for (col = 0; col < COLS; col++) {
            if (col == COLS/2) printf("     ");
            if ((col+1) < COLS) printf("%3d,", ledStripAsTableValues[row][col]);
            else                printf("%3d ", ledStripAsTableValues[row][col]);
        }
        printf("\n");
    }
}


void setupDigitLeds() {
    int i, side, cols, col, row, index;

    // set columns
    cols = SIDES * (4*DIGIT_WIDTH + 2*DIGIT_GAP + SCORE_GAP);

#if TOP_RIGHT == 1
    // start top,left
    index = 0;
    for (row = 0; row < ROWS; row++) {
        col = 0;
        for (side = 0; side < SIDES; side++) {
            if (side == 0) {
                for (i=0; i<DIGIT_WIDTH; i++) {
                    digitLedsA[row][i] = index;
                    col++;
                    index++;
                }
                for (i=0; i<DIGIT_GAP; i++) {
                    col++;
                    index++;
                }
                for (i=0; i<DIGIT_WIDTH; i++) {
                    digitLedsB[row][i] = index;
                    col++;
                    index++;
                }
                for (i=0; i<SCORE_GAP; i++) {
                    col++;
                    index++;
            }
                for (i=0; i<DIGIT_WIDTH; i++) {
                    digitLedsC[row][i] = index;
                    col++;
                    index++;
                }
                for (i=0; i<DIGIT_GAP; i++) {
                    col++;
                    index++;
                }
                for (i=0; i<DIGIT_WIDTH; i++) {
                    digitLedsD[row][i] = index;
                    col++;
                    index++;
                }
            }
#if SIDES == 2
            if (side == 1) {
                for (i=0; i<DIGIT_WIDTH; i++) {
                    digitLedsE[row][i] = index;
                    col++;
                    index++;
                }
                for (i=0; i<DIGIT_GAP; i++) {
                    col++;
                    index++;
                }
                for (i=0; i<DIGIT_WIDTH; i++) {
                    digitLedsF[row][i] = index;
                    col++;
                    index++;
                }
                for (i=0; i<SCORE_GAP; i++) {
                    col++;
                    index++;
                }
                for (i=0; i<DIGIT_WIDTH; i++) {
                    digitLedsG[row][i] = index;
                    col++;
                    index++;
                }
                for (i=0; i<DIGIT_GAP; i++) {
                    col++;
                    index++;
                }
                for (i=0; i<DIGIT_WIDTH; i++) {
                    digitLedsH[row][i] = index;
                    col++;
                    index++;
                }
            }
#endif //SIDES == 2
        }
    }
#endif // TOP_RIGHT=1


#if TOP_RIGHT == 0
    // start bottom,right
    index = (ROWS * COLS) -1;
    for (row = 0; row < ROWS; row++) {
        col = 0;
        for (side = 0; side < SIDES; side++) {
            if (side == 0) {
                for (i=0; i<DIGIT_WIDTH; i++) {
                    digitLeds[DIGITA][row][i] = index;
                    col++;
                    index--;
                }
                for (i=0; i<DIGIT_GAP; i++) {
                    col++;
                    index--;
                }
                for (i=0; i<DIGIT_WIDTH; i++) {
                    digitLeds[DIGITB][row][i] = index;
                    col++;
                    index--;
                }
                for (i=0; i<SCORE_GAP; i++) {
                    col++;
                    index--;
            }
                for (i=0; i<DIGIT_WIDTH; i++) {
                    digitLeds[DIGITC][row][i] = index;
                    col++;
                    index--;
                }
                for (i=0; i<DIGIT_GAP; i++) {
                    col++;
                    index--;
                }
                for (i=0; i<DIGIT_WIDTH; i++) {
                    digitLeds[DIGITD][row][i] = index;
                    col++;
                    index--;
                }
            }
#if SIDES == 2
            if (side == 1) {
                for (i=0; i<DIGIT_WIDTH; i++) {
                    digitLeds[DIGITE][row][i] = index;
                    col++;
                    index--;
                }
                for (i=0; i<DIGIT_GAP; i++) {
                    col++;
                    index--;
                }
                for (i=0; i<DIGIT_WIDTH; i++) {
                    digitLeds[DIGITF][row][i] = index;
                    col++;
                    index--;
                }
                for (i=0; i<SCORE_GAP; i++) {
                    col++;
                    index--;
                }
                for (i=0; i<DIGIT_WIDTH; i++) {
                    digitLeds[DIGITG][row][i] = index;
                    col++;
                    index--;
                }
                for (i=0; i<DIGIT_GAP; i++) {
                    col++;
                    index--;
                }
                for (i=0; i<DIGIT_WIDTH; i++) {
                    digitLeds[DIGITH][row][i] = index;
                    col++;
                    index--;
                }
            }
#endif //SIDES == 2
        }
    }
#endif // TOP_RIGHT=1
 
}






void getOperation() {
    printf("option: ");
    operation = getchar();
}

void clearOperation() {
    getchar();
}

void scoreReset() {
    scoreA = 0;
    scoreB = 0;
}

void scoreSideToggle() {
    sideA = !sideA;
}

void scorePlus() {
    if (sideA) { scoreA += 1; }
    else       { scoreB += 1; }
}

void scoreMinus() {
    if (sideA) { scoreA -= 1; }
    else       { scoreB -= 1; }
    if (scoreA < 0) { scoreA = 0; }
    if (scoreB < 0) { scoreB = 0; }
}

void clearDigit(int digitNum, int val) {
    int i,j;
    for (i=0; i < ROWS; i++) {
        for (j=0; j < DIGIT_WIDTH; j++) {
            digits[digitNum][i][j] = val;
        }     
    }
}

void clearDigitLeds() {
    clearDigit(DIGITA, -1);
    clearDigit(DIGITB, -1);
    clearDigit(DIGITC, -1);
    clearDigit(DIGITD, -1);
#if SIDES == 2
    clearDigit(DIGITE, -1);
    clearDigit(DIGITF, -1);
    clearDigit(DIGITG, -1);
    clearDigit(DIGITH, -1);
#endif
}

void clearDigits() {
    clearDigit(DIGITA, 0);
    clearDigit(DIGITB, 0);
    clearDigit(DIGITC, 0);
    clearDigit(DIGITD, 0);
#if SIDES == 2
    clearDigit(DIGITE, 0);
    clearDigit(DIGITF, 0);
    clearDigit(DIGITG, 0);
    clearDigit(DIGITH, 0);
#endif
}



void setSegments(int digitNum, int seg1, int seg2, int seg3, int seg4, int seg5, int seg6, int seg7) {
    int i, temp;
    //printf("%d %d %d %d %d %d %d\n", seg1, seg2, seg3, seg4, seg5, seg6, seg7);
    clearDigit(digitNum, 0);
    if (seg1) {
        for (i=0; i<DIGIT_WIDTH; i++) digits[digitNum][0][i] = 1;
    }
    if (seg2) {
        temp = (ROWS-1)/2;
        for (i=0; i<temp; i++) digits[digitNum][i][DIGIT_WIDTH-1] = 1;
    }
    if (seg3) {
        temp = (ROWS-1)/2;
        for (i=temp; i<ROWS; i++) digits[digitNum][i][DIGIT_WIDTH-1] = 1;
    }
    if (seg4) {
        temp = (ROWS-1);
        for (i=0; i<DIGIT_WIDTH; i++) digits[digitNum][temp][i] = 1;
    }
    if (seg5) {
        temp = (ROWS-1)/2;
        for (i=temp; i<ROWS; i++) digits[digitNum][i][0] = 1;
    }
    if (seg6) {
        temp = (ROWS-1)/2;
        for (i=0; i<temp; i++) digits[digitNum][i][0] = 1;
    }
    if (seg7) {
        temp = (ROWS-1)/2;
        for (i=0; i<DIGIT_WIDTH; i++) digits[digitNum][temp][i] = 1;
    }
}

//          seg1
//     seg6     seg2
//          seg7
//     seg5     seg3
//          seg4
void setDigit(int digitNum, int val) {
    switch (val) {
        case -1: clearDigit(digitNum, 0);              break;
        case  0: setSegments(digitNum, 1,1,1,1,1,1,0); break;
        case  1: setSegments(digitNum, 0,1,1,0,0,0,0); break;
        case  2: setSegments(digitNum, 1,1,0,1,1,0,1); break;
        case  3: setSegments(digitNum, 1,1,1,1,0,0,1); break;
        case  4: setSegments(digitNum, 0,1,1,0,0,1,1); break;
        case  5: setSegments(digitNum, 1,0,1,1,0,1,1); break;
        case  6: setSegments(digitNum, 1,0,1,1,1,1,1); break;
        case  7: setSegments(digitNum, 1,1,1,0,0,0,0); break;
        case  8: setSegments(digitNum, 1,1,1,1,1,1,1); break;
        case  9: setSegments(digitNum, 1,1,1,1,0,1,1); break;
    }
}

void setDigits() {
    int nibble;

#ifdef SCORE_PRINT
    printf("%s %02d  %02d %s\n", 
        (sideA ? ">" : " "),
        scoreA,
        scoreB,
        (sideA ? " " : "<")
    );
#endif

    nibble = scoreA/10;
    setDigit(DIGITA, nibble);
    nibble = scoreA%10;
    setDigit(DIGITB, nibble);
    nibble = scoreB/10;
    setDigit(DIGITC, nibble);
    nibble = scoreB%10;
    setDigit(DIGITD, nibble);
#if SIDES == 2
    nibble = scoreA/10;
    setDigit(DIGITE, nibble);
    nibble = scoreA%10;
    setDigit(DIGITF, nibble);
    nibble = scoreB/10;
    setDigit(DIGITG, nibble);
    nibble = scoreB%10;
    setDigit(DIGITH, nibble);
#endif
}



void dumpDigitLine(int digitNum, int row, char *post) {
    int col;
    for (col=0; col < DIGIT_WIDTH; col++) {
        if (digits[digitNum][row][col]) printf("%3s ", "X");
        else                 printf("%3s ", " ");
    } 
    printf("%s", post);
}

void dumpDigitLeds() {
    int row,j;
    for (row=0; row < ROWS; row++) {
        dumpDigitLine(DIGITA, row, " ");
        dumpDigitLine(DIGITB, row, "    ");
        dumpDigitLine(DIGITC, row, " ");
#if SIDES == 1
        dumpDigitLine(DIGITD, row, "\n");
#endif
#if SIDES == 2
        dumpDigitLine(DIGITD, row, "  ...  ");
        dumpDigitLine(DIGITE, row, " ");
        dumpDigitLine(DIGITF, row, "    ");
        dumpDigitLine(DIGITG, row, " ");
        dumpDigitLine(DIGITH, row, "\n");
#endif  
    }
    printf("\n");
}

void dumpDigits() {
    int row,j;
    for (row=0; row < ROWS; row++) {
        dumpDigitLine(DIGITA, row, " ");
        dumpDigitLine(DIGITB, row, "    ");
        dumpDigitLine(DIGITC, row, " ");
#if SIDES == 1
        dumpDigitLine(DIGITD, row, "\n");
#endif
#if SIDES == 2
        dumpDigitLine(DIGITD, row, "  ...  ");
        dumpDigitLine(DIGITE, row, " ");
        dumpDigitLine(DIGITF, row, "    ");
        dumpDigitLine(DIGITG, row, " ");
        dumpDigitLine(DIGITH, row, "\n");
#endif  
    }
    printf("\n");
}


#ifdef TEST_SEQUENCE
void testSeq() {
    // setup
    clearDigits();
    clearDigitLeds();
    setupDigitLeds();

    setDigits();
    dumpDigits();

    scorePlus();
    setDigits();
    dumpDigits();

    scorePlus();
    setDigits();
    dumpDigits();

    scoreSideToggle();
    scorePlus();
    setDigits();
    dumpDigits();

    scoreMinus();
    setDigits();
    dumpDigits();

    scoreReset();
    setDigits();
    dumpDigits();
}
#endif // TEST_SEQUENCE





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
        case 'r': scoreReset(); break;
        case 's': scoreSideToggle(); break;
        case 'p': scorePlus(); break;
        case 'm': scoreMinus(); break;
#ifdef SIMULATION
        case '?' :
        case 'h' : usage(); break;
#endif
    }
    clearOperation();
    setDigits();
    dumpDigits();
}


////////////////////////////////////////////////////////////////////////////////
// Main
////////////////////////////////////////////////////////////////////////////////
int main(void) {

#ifdef TEST_SEQUENCE
    //testSeq();
#endif

dumpLedStripAsTableValues();
ledStripAsTableValues[0][2] = 1;
ledStripAsTableValues[1][2] = 1;
ledStripAsTableValues[2][2] = 1;
ledStripAsTableValues[3][2] = 1;
ledStripAsTableValues[4][2] = 1;
dumpLedStripAsTableValues();

    setup();
    while (1) {
        loop();
    }
    return 0;
}


// TODO:
// - set leds from digits/scores
// - can we generate code to drop in .ino from .c?

