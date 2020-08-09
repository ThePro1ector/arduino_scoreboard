
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// rm -f ./runme ; gcc models.c -o runme ; ./runme

// C version to test ideas faster without loading on Arduino

// #define TOP_RIGHT       1
// #define START_LED       0
// #define COLS            (2*15)
// #define ROWS            5
// #define SIDES           2
// #define DIGIT_WIDTH_MSB 3
// #define DIGIT_WIDTH_LSB 3
// #define DIGIT_GAP       0
// #define SCORE_GAP       3

// First Prototype
#define TOP_RIGHT       1
#define START_LED       (150 - 10*11)
#define COLS            (2*11)
#define ROWS            5
#define SIDES           2
#define DIGIT_WIDTH_MSB 1
#define DIGIT_WIDTH_LSB 3
#define DIGIT_GAP       0
#define SCORE_GAP       3
#define MAX_SCORE       19


void clearTable(int table[ROWS][COLS], int val) {
    int col, row;
    for (row = 0; row < ROWS; row++) {
        for (col = 0; col < COLS; col++) {
            table[row][col] = val;
        }
    }
}

void setDigitValuesMSB(int digit[ROWS][DIGIT_WIDTH_MSB], int val) {
    int col, row;
    for (row = 0; row < ROWS; row++) {
        for (col = 0; col < DIGIT_WIDTH_MSB; col++) {
            digit[row][col] = val;
        }
    }
}

void setDigitValuesLSB(int digit[ROWS][DIGIT_WIDTH_LSB], int val) {
    int col, row;
    for (row = 0; row < ROWS; row++) {
        for (col = 0; col < DIGIT_WIDTH_LSB; col++) {
            digit[row][col] = val;
        }
    }
}

void dumpTable(int table[ROWS][COLS], char *name) {
    int col, row;
    printf("int %s[ROWS][COLS] = {\n", name);
    for (row = 0; row < ROWS; row++) {
        printf("  {");
        for (col = 0; col < COLS; col++) {
#if SIDES == 2
            if (col == COLS/2) printf("     ");
#endif
            if ((col+1) < COLS) printf("%3d,", table[row][col]);
            else                printf("%3d ", table[row][col]);
        }
        if ((row+1) < ROWS) printf("},\n");
        else                printf("}\n");
    }
    printf("};\n");
}

void dumpDigitMSB(int digit[ROWS][DIGIT_WIDTH_MSB], char *name) {
    int col, row;
    printf("int %s[ROWS][DIGIT_WIDTH_MSB] = {\n", name);
    for (row = 0; row < ROWS; row++) {
        printf("  {");
        for (col = 0; col < DIGIT_WIDTH_MSB; col++) {
            if ((col+1) < DIGIT_WIDTH_MSB) printf("%3d,", digit[row][col]);
            else                printf("%3d ", digit[row][col]);
        }
        if ((row+1) < ROWS) printf("},\n");
        else                printf("}\n");
    }
    printf("};\n");
}

void dumpDigitLSB(int digit[ROWS][DIGIT_WIDTH_LSB], char *name) {
    int col, row;
    printf("int %s[ROWS][DIGIT_WIDTH_LSB] = {\n", name);
    for (row = 0; row < ROWS; row++) {
        printf("  {");
        for (col = 0; col < DIGIT_WIDTH_LSB; col++) {
            if ((col+1) < DIGIT_WIDTH_LSB) printf("%3d,", digit[row][col]);
            else                printf("%3d ", digit[row][col]);
        }
        if ((row+1) < ROWS) printf("},\n");
        else                printf("}\n");
    }
    printf("};\n");
}


void printLedArrays() {
    int i, side, cols, col, row, index;
    int maxScore = 0;
    int table[ROWS][COLS];
    int digitA[ROWS][DIGIT_WIDTH_MSB];
    int digitB[ROWS][DIGIT_WIDTH_LSB];
    int digitC[ROWS][DIGIT_WIDTH_MSB];
    int digitD[ROWS][DIGIT_WIDTH_LSB];
    int digitE[ROWS][DIGIT_WIDTH_MSB];
    int digitF[ROWS][DIGIT_WIDTH_LSB];
    int digitG[ROWS][DIGIT_WIDTH_MSB];
    int digitH[ROWS][DIGIT_WIDTH_LSB];

    clearTable(table, -1);
#if TOP_RIGHT == 1
    // start top,left
    index = START_LED;
    if (START_LED == -1) index = 0;
    for (row = 0; row < ROWS; row++) {
        col = 0;
        for (i=0; i<DIGIT_WIDTH_MSB; i++) {
            table[row][col] = index;
            digitA[row][i] = index;
            col++;
            index++;
        }
        for (i=0; i<DIGIT_GAP; i++) {
            col++;
            index++;
        }
        for (i=0; i<DIGIT_WIDTH_LSB; i++) {
            table[row][col] = index;
            digitB[row][i] = index;
            col++;
            index++;
        }
        for (i=0; i<SCORE_GAP; i++) {
            col++;
            index++;
        }
        for (i=0; i<DIGIT_WIDTH_MSB; i++) {
            table[row][col] = index;
            digitC[row][i] = index;
            col++;
            index++;
        }
        for (i=0; i<DIGIT_GAP; i++) {
            col++;
            index++;
        }
        for (i=0; i<DIGIT_WIDTH_LSB; i++) {
            table[row][col] = index;
            digitD[row][i] = index;
            col++;
            index++;
        }
#if SIDES == 2
        for (i=0; i<DIGIT_WIDTH_MSB; i++) {
            table[row][col] = index;
            digitE[row][i] = index;
            col++;
            index++;
        }
        for (i=0; i<DIGIT_GAP; i++) {
            col++;
            index++;
        }
        for (i=0; i<DIGIT_WIDTH_LSB; i++) {
            table[row][col] = index;
            digitF[row][i] = index;
            col++;
            index++;
        }
        for (i=0; i<SCORE_GAP; i++) {
            col++;
            index++;
        }
        for (i=0; i<DIGIT_WIDTH_MSB; i++) {
            table[row][col] = index;
            digitG[row][i] = index;
            col++;
            index++;
        }
        for (i=0; i<DIGIT_GAP; i++) {
            col++;
            index++;
        }
        for (i=0; i<DIGIT_WIDTH_LSB; i++) {
            table[row][col] = index;
            digitH[row][i] = index;
            col++;
            index++;
        }
#endif // SIDES == 2
    }
#endif // TOP_RIGHT=1


#if TOP_RIGHT == 0
    // start bottom,right
    index = START_LED;
    if (START_LED == -1) index = (ROWS * COLS) -1;
    index = START_LED;
    if (START_LED == -1) index = 0;
    for (row = 0; row < ROWS; row++) {
        col = 0;
        for (i=0; i<DIGIT_WIDTH_MSB; i++) {
            table[row][col] = index;
            digitA[row][i] = index;
            col++;
            index--;
        }
        for (i=0; i<DIGIT_GAP; i++) {
            col++;
            index--;
        }
        for (i=0; i<DIGIT_WIDTH_LSB; i++) {
            table[row][col] = index;
            digitB[row][i] = index;
            col++;
            index--;
        }
        for (i=0; i<SCORE_GAP; i++) {
            col++;
            index--;
        }
        for (i=0; i<DIGIT_WIDTH_MSB; i++) {
            table[row][col] = index;
            digitC[row][i] = index;
            col++;
            index--;
        }
        for (i=0; i<DIGIT_GAP; i++) {
            col++;
            index--;
        }
        for (i=0; i<DIGIT_WIDTH_LSB; i++) {
            table[row][col] = index;
            digitD[row][i] = index;
            col++;
            index--;
        }
#if SIDES == 2
        for (i=0; i<DIGIT_WIDTH_MSB; i++) {
            table[row][col] = index;
            digitE[row][i] = index;
            col++;
            index--;
        }
        for (i=0; i<DIGIT_GAP; i++) {
            col++;
            index--;
        }
        for (i=0; i<DIGIT_WIDTH_LSB; i++) {
            table[row][col] = index;
            digitF[row][i] = index;
            col++;
            index--;
        }
        for (i=0; i<SCORE_GAP; i++) {
            col++;
            index--;
        }
        for (i=0; i<DIGIT_WIDTH_MSB; i++) {
            table[row][col] = index;
            digitG[row][i] = index;
            col++;
            index--;
        }
        for (i=0; i<DIGIT_GAP; i++) {
            col++;
            index--;
        }
        for (i=0; i<DIGIT_WIDTH_LSB; i++) {
            table[row][col] = index;
            digitH[row][i] = index;
            col++;
            index--;
        }
#endif // SIDES == 2
    }
#endif // TOP_RIGHT=1

    dumpTable(table, "ledTable");
    dumpDigitMSB(digitA, "digitA");
    dumpDigitLSB(digitB, "digitB");
    dumpDigitMSB(digitC, "digitC");
    dumpDigitLSB(digitD, "digitD");
    dumpDigitMSB(digitE, "digitE");
    dumpDigitLSB(digitF, "digitF");
    dumpDigitMSB(digitG, "digitG");
    dumpDigitLSB(digitH, "digitH");

    // verify columns
    cols = SIDES * (2*(DIGIT_WIDTH_MSB+DIGIT_WIDTH_LSB) + 2*DIGIT_GAP + SCORE_GAP);
    if (cols != COLS) {
        printf("WARNING: estimated col (%d) != COL (%d)\n", cols, COLS);
    }
}





////////////////////////////////////////////////////////////////////////////////////////////////////////////
// copy the code below to .ino file
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define SIMULATED
//#define ARDUINO

// TODO: uncomment in .ino file
// #define TOP_RIGHT       1
// #define START_LED       40
// #define COLS            22
// #define ROWS            5
// #define SIDES           2
// #define DIGIT_WIDTH_MSB 1
// #define DIGIT_WIDTH_LSB 3
// #define DIGIT_GAP       0
// #define SCORE_GAP       3
// #define MAX_SCORE       19



// TODO change to variables for sides
#define LED_LEVELR 1
#define LED_LEVELG 1
#define LED_LEVELB 1

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

int side1 = 1;
int score1 = 0;
int score2 = 0;

int ledTable[ROWS][COLS] = {
  { 40, 41, 42, 43, -1, -1, -1, 47, 48, 49, 50,      51, 52, 53, 54, -1, -1, -1, 58, 59, 60, 61 },
  { 62, 63, 64, 65, -1, -1, -1, 69, 70, 71, 72,      73, 74, 75, 76, -1, -1, -1, 80, 81, 82, 83 },
  { 84, 85, 86, 87, -1, -1, -1, 91, 92, 93, 94,      95, 96, 97, 98, -1, -1, -1,102,103,104,105 },
  {106,107,108,109, -1, -1, -1,113,114,115,116,     117,118,119,120, -1, -1, -1,124,125,126,127 },
  {128,129,130,131, -1, -1, -1,135,136,137,138,     139,140,141,142, -1, -1, -1,146,147,148,149 }
};
int digitA[ROWS][DIGIT_WIDTH_MSB] = {
  { 40 },
  { 62 },
  { 84 },
  {106 },
  {128 }
};
int digitB[ROWS][DIGIT_WIDTH_LSB] = {
  { 41, 42, 43 },
  { 63, 64, 65 },
  { 85, 86, 87 },
  {107,108,109 },
  {129,130,131 }
};
int digitC[ROWS][DIGIT_WIDTH_MSB] = {
  { 47 },
  { 69 },
  { 91 },
  {113 },
  {135 }
};
int digitD[ROWS][DIGIT_WIDTH_LSB] = {
  { 48, 49, 50 },
  { 70, 71, 72 },
  { 92, 93, 94 },
  {114,115,116 },
  {136,137,138 }
};
int digitE[ROWS][DIGIT_WIDTH_MSB] = {
  { 51 },
  { 73 },
  { 95 },
  {117 },
  {139 }
};
int digitF[ROWS][DIGIT_WIDTH_LSB] = {
  { 52, 53, 54 },
  { 74, 75, 76 },
  { 96, 97, 98 },
  {118,119,120 },
  {140,141,142 }
};
int digitG[ROWS][DIGIT_WIDTH_MSB] = {
  { 58 },
  { 80 },
  {102 },
  {124 },
  {146 }
};
int digitH[ROWS][DIGIT_WIDTH_LSB] = {
  { 59, 60, 61 },
  { 81, 82, 83 },
  {103,104,105 },
  {125,126,127 },
  {147,148,149 }
};




int ledStripAsTable[5][22] = {
  {  40,  41,  42,  43,  -1,  -1,  -1,  47,  48,  49,  50,       51,  52,  53,  54,  -1,  -1,  -1,  58,  59,  60,  61 },
  {  62,  63,  64,  65,  -1,  -1,  -1,  69,  70,  71,  72,       73,  74,  75,  76,  -1,  -1,  -1,  80,  81,  82,  83 },
  {  84,  85,  86,  87,  -1,  -1,  -1,  91,  92,  93,  94,       95,  96,  97,  98,  -1,  -1,  -1, 102, 103, 104, 105 },
  { 106, 107, 108, 109,  -1,  -1,  -1, 113, 114, 115, 116,      117, 118, 119, 120,  -1,  -1,  -1, 124, 125, 126, 127 },
  { 128, 129, 130, 131,  -1,  -1,  -1, 135, 136, 137, 138,      139, 140, 141, 142,  -1,  -1,  -1, 146, 147, 148, 149 }
};
#ifdef SIMULATED
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
#if SIDES == 2
            if (col == COLS/2) printf("     ");
#endif
            if ((col+1) < COLS) printf("%3d,", ledStripAsTableValues[row][col]);
            else                printf("%3d ", ledStripAsTableValues[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}
#endif // SIMULATED



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
            if (position == ledStripAsTable[row][col]) {
                ledStripAsTableValues[row][col] = value;
                break;
            }     
        }
    }
#endif // SIMULATED
}


void clearDigit(int digitNum, int val) {
    // int i,j;
    // for (i=0; i < ROWS; i++) {
    //     for (j=0; j < DIGIT_WIDTH; j++) {
    //         digits[digitNum][i][j] = val;
    //     }     
    // }
}

void setSegments(int digitNum, int seg1, int seg2, int seg3, int seg4, int seg5, int seg6, int seg7) {
    // int i, temp;
    // //printf("%d %d %d %d %d %d %d\n", seg1, seg2, seg3, seg4, seg5, seg6, seg7);
    // clearDigit(digitNum, 0);
    // if (seg1) {
    //     for (i=0; i<DIGIT_WIDTH; i++) digits[digitNum][0][i] = 1;
    // }
    // if (seg2) {
    //     temp = (ROWS-1)/2;
    //     for (i=0; i<temp; i++) digits[digitNum][i][DIGIT_WIDTH-1] = 1;
    // }
    // if (seg3) {
    //     temp = (ROWS-1)/2;
    //     for (i=temp; i<ROWS; i++) digits[digitNum][i][DIGIT_WIDTH-1] = 1;
    // }
    // if (seg4) {
    //     temp = (ROWS-1);
    //     for (i=0; i<DIGIT_WIDTH; i++) digits[digitNum][temp][i] = 1;
    // }
    // if (seg5) {
    //     temp = (ROWS-1)/2;
    //     for (i=temp; i<ROWS; i++) digits[digitNum][i][0] = 1;
    // }
    // if (seg6) {
    //     temp = (ROWS-1)/2;
    //     for (i=0; i<temp; i++) digits[digitNum][i][0] = 1;
    // }
    // if (seg7) {
    //     temp = (ROWS-1)/2;
    //     for (i=0; i<DIGIT_WIDTH; i++) digits[digitNum][temp][i] = 1;
    // }
}

void updateDigit(int digitNum, int value) {
    switch (value) {
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
#if SIDES == 2
    nibble = score1/10;
    updateDigit(DIGITE, nibble);
    nibble = score1%10;
    updateDigit(DIGITF, nibble);
    nibble = score2/10;
    updateDigit(DIGITG, nibble);
    nibble = score2%10;
    updateDigit(DIGITH, nibble);
#endif
}

void scoresReset() {
    score1 = 0;
    score2 = 0;
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// copy the code above to .ino file
////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
// Main
////////////////////////////////////////////////////////////////////////////////
int main(void) {

    printLedArrays();
    // printLedArraysValues();

    // dumpLedStripAsTableValues();

    // scoresReset();
    // updateScores();
    // dumpLedStripAsTableValues();

    // scoresPlus();
    // updateScores();
    // dumpLedStripAsTableValues();

    // scoresPlus();
    // updateScores();
    // dumpLedStripAsTableValues();

    // scoresSide();

    // scoresPlus();
    // updateScores();
    // dumpLedStripAsTableValues();

    // scoresPlus();
    // updateScores();
    // dumpLedStripAsTableValues();

    // scoresMinus();
    // updateScores();
    // dumpLedStripAsTableValues();

    // scoresReset();
    // updateScores();
    // dumpLedStripAsTableValues();
}

