
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// rm -f ./runme ; gcc models.c -o runme ; ./runme

// C version to test ideas faster without loading on Arduino

#define TOP_RIGHT       1
#define START_LED       0
#define COLS            (2*15)
#define ROWS            5
#define SIDES           2  // NOTE: cannot change yet
#define DIGIT_WIDTH     3
#define DIGIT_GAP       0
#define SCORE_GAP       3
#define MAX_SCORE       99



void clearTable(int table[ROWS][COLS], int val) {
    int col, row;
    for (row = 0; row < ROWS; row++) {
        for (col = 0; col < COLS; col++) {
            table[row][col] = val;
        }
    }
}

void setDigitValues(int digit[ROWS][DIGIT_WIDTH], int val) {
    int col, row;
    for (row = 0; row < ROWS; row++) {
        for (col = 0; col < DIGIT_WIDTH; col++) {
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
            if (col == COLS/2) printf("     ");
            if ((col+1) < COLS) printf("%3d,", table[row][col]);
            else                printf("%3d", table[row][col]);
        }
        if ((row+1) < ROWS) printf("},\n");
        else                printf("}\n");
    }
    printf("};\n");
}

void dumpDigitArray(int digit[ROWS][DIGIT_WIDTH], char *name) {
    int col, row;
    printf("int %s[ROWS][DIGIT_WIDTH] = {\n", name);
    for (row = 0; row < ROWS; row++) {
        printf("  {");
        for (col = 0; col < DIGIT_WIDTH; col++) {
            if ((col+1) < DIGIT_WIDTH) printf("%3d,", digit[row][col]);
            else                printf("%3d ", digit[row][col]);
        }
        if ((row+1) < ROWS) printf("},\n");
        else                printf("}\n");
    }
    printf("};\n");
}

void dumpNumArray(int digit[ROWS][DIGIT_WIDTH]) {
    int col, row;
    printf("{\n");
    for (row = 0; row < ROWS; row++) {
        printf("  {");
        for (col = 0; col < DIGIT_WIDTH; col++) {
            if ((col+1) < DIGIT_WIDTH) printf("%3d,", digit[row][col]);
            else                printf("%3d ", digit[row][col]);
        }
        if ((row+1) < ROWS) printf("},\n");
        else                printf("}\n");
    }
    printf("},\n");
}



void printLedArrays() {
    int i, side, cols, col, row, index;
    int table[ROWS][COLS];
    int tableValues[ROWS][COLS];
    int digitA[ROWS][DIGIT_WIDTH];
    int digitB[ROWS][DIGIT_WIDTH];
    int digitC[ROWS][DIGIT_WIDTH];
    int digitD[ROWS][DIGIT_WIDTH];
    int digitE[ROWS][DIGIT_WIDTH];
    int digitF[ROWS][DIGIT_WIDTH];
    int digitG[ROWS][DIGIT_WIDTH];
    int digitH[ROWS][DIGIT_WIDTH];

    clearTable(table, -1);
#if TOP_RIGHT == 1
    // start top,left
    index = START_LED;
    if (START_LED == -1) index = 0;
    for (row = 0; row < ROWS; row++) {
        col = 0;
        for (i=0; i<DIGIT_WIDTH; i++) {
            table[row][col] = index;
            digitA[row][i] = index;
            col++;
            index++;
        }
        for (i=0; i<DIGIT_GAP; i++) {
            col++;
            index++;
        }
        for (i=0; i<DIGIT_WIDTH; i++) {
            table[row][col] = index;
            digitB[row][i] = index;
            col++;
            index++;
        }
        for (i=0; i<SCORE_GAP; i++) {
            col++;
            index++;
        }
        for (i=0; i<DIGIT_WIDTH; i++) {
            table[row][col] = index;
            digitC[row][i] = index;
            col++;
            index++;
        }
        for (i=0; i<DIGIT_GAP; i++) {
            col++;
            index++;
        }
        for (i=0; i<DIGIT_WIDTH; i++) {
            table[row][col] = index;
            digitD[row][i] = index;
            col++;
            index++;
        }
        for (i=0; i<DIGIT_WIDTH; i++) {
            table[row][col] = index;
            digitE[row][i] = index;
            col++;
            index++;
        }
        for (i=0; i<DIGIT_GAP; i++) {
            col++;
            index++;
        }
        for (i=0; i<DIGIT_WIDTH; i++) {
            table[row][col] = index;
            digitF[row][i] = index;
            col++;
            index++;
        }
        for (i=0; i<SCORE_GAP; i++) {
            col++;
            index++;
        }
        for (i=0; i<DIGIT_WIDTH; i++) {
            table[row][col] = index;
            digitG[row][i] = index;
            col++;
            index++;
        }
        for (i=0; i<DIGIT_GAP; i++) {
            col++;
            index++;
        }
        for (i=0; i<DIGIT_WIDTH; i++) {
            table[row][col] = index;
            digitH[row][i] = index;
            col++;
            index++;
        }
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
        for (i=0; i<DIGIT_WIDTH; i++) {
            table[row][col] = index;
            digitA[row][i] = index;
            col++;
            index--;
        }
        for (i=0; i<DIGIT_GAP; i++) {
            col++;
            index--;
        }
        for (i=0; i<DIGIT_WIDTH; i++) {
            table[row][col] = index;
            digitB[row][i] = index;
            col++;
            index--;
        }
        for (i=0; i<SCORE_GAP; i++) {
            col++;
            index--;
        }
        for (i=0; i<DIGIT_WIDTH; i++) {
            table[row][col] = index;
            digitC[row][i] = index;
            col++;
            index--;
        }
        for (i=0; i<DIGIT_GAP; i++) {
            col++;
            index--;
        }
        for (i=0; i<DIGIT_WIDTH; i++) {
            table[row][col] = index;
            digitD[row][i] = index;
            col++;
            index--;
        }
        for (i=0; i<DIGIT_WIDTH; i++) {
            table[row][col] = index;
            digitE[row][i] = index;
            col++;
            index--;
        }
        for (i=0; i<DIGIT_GAP; i++) {
            col++;
            index--;
        }
        for (i=0; i<DIGIT_WIDTH; i++) {
            table[row][col] = index;
            digitF[row][i] = index;
            col++;
            index--;
        }
        for (i=0; i<SCORE_GAP; i++) {
            col++;
            index--;
        }
        for (i=0; i<DIGIT_WIDTH; i++) {
            table[row][col] = index;
            digitG[row][i] = index;
            col++;
            index--;
        }
        for (i=0; i<DIGIT_GAP; i++) {
            col++;
            index--;
        }
        for (i=0; i<DIGIT_WIDTH; i++) {
            table[row][col] = index;
            digitH[row][i] = index;
            col++;
            index--;
        }
    }
#endif // TOP_RIGHT=1

    for (row = 0; row < ROWS; row++) {
        for (col = 0; col < COLS; col++) {
            tableValues[row][col] = 0;
        }
    }

    dumpTable(table, "ledTable");
    dumpTable(tableValues, "ledTableValues");
    dumpDigitArray(digitA, "digitA");
    dumpDigitArray(digitB, "digitB");
    dumpDigitArray(digitC, "digitC");
    dumpDigitArray(digitD, "digitD");
    dumpDigitArray(digitE, "digitE");
    dumpDigitArray(digitF, "digitF");
    dumpDigitArray(digitG, "digitG");
    dumpDigitArray(digitH, "digitH");

    // verify columns
    cols = SIDES * (2*(DIGIT_WIDTH+DIGIT_WIDTH) + 2*DIGIT_GAP + SCORE_GAP);
    if (cols != COLS) {
        printf("WARNING: estimated col (%d) != COL (%d)\n", cols, COLS);
    }
}


void setSegments(int numArray[ROWS][DIGIT_WIDTH], int seg1, int seg2, int seg3, int seg4, int seg5, int seg6, int seg7) {
    int i, temp;
    //printf("%d %d %d %d %d %d %d\n", seg1, seg2, seg3, seg4, seg5, seg6, seg7);
    setDigitValues(numArray, 0);
    if (seg1) {
        for (i=0; i<DIGIT_WIDTH; i++) numArray[0][i] = 1;
    }
    if (seg2) {
        temp = (ROWS-1)/2;
        for (i=0; i<temp; i++) numArray[i][DIGIT_WIDTH-1] = 1;
    }
    if (seg3) {
        temp = (ROWS-1)/2;
        for (i=temp; i<ROWS; i++) numArray[i][DIGIT_WIDTH-1] = 1;
    }
    if (seg4) {
        temp = (ROWS-1);
        for (i=0; i<DIGIT_WIDTH; i++) numArray[temp][i] = 1;
    }
    if (seg5) {
        temp = (ROWS-1)/2;
        for (i=temp; i<ROWS; i++) numArray[i][0] = 1;
    }
    if (seg6) {
        temp = (ROWS-1)/2;
        for (i=0; i<temp; i++) numArray[i][0] = 1;
    }
    if (seg7) {
        temp = (ROWS-1)/2;
        for (i=0; i<DIGIT_WIDTH; i++) numArray[temp][i] = 1;
    }
}

void printNumArrays() {
    int num0[ROWS][DIGIT_WIDTH];
    int num1[ROWS][DIGIT_WIDTH];
    int num2[ROWS][DIGIT_WIDTH];
    int num3[ROWS][DIGIT_WIDTH];
    int num4[ROWS][DIGIT_WIDTH];
    int num5[ROWS][DIGIT_WIDTH];
    int num6[ROWS][DIGIT_WIDTH];
    int num7[ROWS][DIGIT_WIDTH];
    int num8[ROWS][DIGIT_WIDTH];
    int num9[ROWS][DIGIT_WIDTH];

    setSegments(num0, 1,1,1,1,1,1,0);
    setSegments(num1, 0,1,1,0,0,0,0);
    setSegments(num2, 1,1,0,1,1,0,1);
    setSegments(num3, 1,1,1,1,0,0,1);
    setSegments(num4, 0,1,1,0,0,1,1);
    setSegments(num5, 1,0,1,1,0,1,1);
    setSegments(num6, 1,0,1,1,1,1,1);
    setSegments(num7, 1,1,1,0,0,0,0);
    setSegments(num8, 1,1,1,1,1,1,1);
    setSegments(num9, 1,1,1,1,0,1,1);

    printf("int numArrays[10][ROWS][COLS] = {\n");
    dumpNumArray(num0);
    dumpNumArray(num1);
    dumpNumArray(num2);
    dumpNumArray(num3);
    dumpNumArray(num4);
    dumpNumArray(num5);
    dumpNumArray(num6);
    dumpNumArray(num7);
    dumpNumArray(num8);
    dumpNumArray(num9);
    printf("};\n");

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// copy the code below to .ino file
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define SIMULATED
//#define ARDUINO

// TODO: copy defines to .ino file



// TODO change to variables for sides
#define LED_LEVELR 1
#define LED_LEVELG 1
#define LED_LEVELB 1

int side1 = 1;
int score1 = 0;
int score2 = 0;

int ledTable[ROWS][COLS] = {
  {  0,  1,  2,  3,  4,  5, -1, -1, -1,  9, 10, 11, 12, 13, 14,      15, 16, 17, 18, 19, 20, -1, -1, -1, 24, 25, 26, 27, 28, 29 },
  { 30, 31, 32, 33, 34, 35, -1, -1, -1, 39, 40, 41, 42, 43, 44,      45, 46, 47, 48, 49, 50, -1, -1, -1, 54, 55, 56, 57, 58, 59 },
  { 60, 61, 62, 63, 64, 65, -1, -1, -1, 69, 70, 71, 72, 73, 74,      75, 76, 77, 78, 79, 80, -1, -1, -1, 84, 85, 86, 87, 88, 89 },
  { 90, 91, 92, 93, 94, 95, -1, -1, -1, 99,100,101,102,103,104,     105,106,107,108,109,110, -1, -1, -1,114,115,116,117,118,119 },
  {120,121,122,123,124,125, -1, -1, -1,129,130,131,132,133,134,     135,136,137,138,139,140, -1, -1, -1,144,145,146,147,148,149 }
};
int ledTableValues[ROWS][COLS] = {
  {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
  {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
  {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
  {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
  {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }
};
int digitA[ROWS][DIGIT_WIDTH] = {
  {  0,  1,  2 },
  { 30, 31, 32 },
  { 60, 61, 62 },
  { 90, 91, 92 },
  {120,121,122 }
};
int digitB[ROWS][DIGIT_WIDTH] = {
  {  3,  4,  5 },
  { 33, 34, 35 },
  { 63, 64, 65 },
  { 93, 94, 95 },
  {123,124,125 }
};
int digitC[ROWS][DIGIT_WIDTH] = {
  {  9, 10, 11 },
  { 39, 40, 41 },
  { 69, 70, 71 },
  { 99,100,101 },
  {129,130,131 }
};
int digitD[ROWS][DIGIT_WIDTH] = {
  { 12, 13, 14 },
  { 42, 43, 44 },
  { 72, 73, 74 },
  {102,103,104 },
  {132,133,134 }
};
int digitE[ROWS][DIGIT_WIDTH] = {
  { 15, 16, 17 },
  { 45, 46, 47 },
  { 75, 76, 77 },
  {105,106,107 },
  {135,136,137 }
};
int digitF[ROWS][DIGIT_WIDTH] = {
  { 18, 19, 20 },
  { 48, 49, 50 },
  { 78, 79, 80 },
  {108,109,110 },
  {138,139,140 }
};
int digitG[ROWS][DIGIT_WIDTH] = {
  { 24, 25, 26 },
  { 54, 55, 56 },
  { 84, 85, 86 },
  {114,115,116 },
  {144,145,146 }
};
int digitH[ROWS][DIGIT_WIDTH] = {
  { 27, 28, 29 },
  { 57, 58, 59 },
  { 87, 88, 89 },
  {117,118,119 },
  {147,148,149 }
};
int numArrays[10][ROWS][COLS] = {
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



void updateScores() {
#ifdef SIMULATED
    printf("%s %02d  %02d %s\n", 
    (side1 ? ">" : " "),
    score1,
    score2,
    (side1 ? " " : "<")
    );
#endif

    // int nibble;
    // nibble = score1/10;
    // updateDigit(DIGITA, nibble);
    // nibble = score1%10;
    // updateDigit(DIGITB, nibble);
    // nibble = score2/10;
    // updateDigit(DIGITC, nibble);
    // nibble = score2%10;
    // updateDigit(DIGITD, nibble);
    // nibble = score1/10;
    // updateDigit(DIGITE, nibble);
    // nibble = score1%10;
    // updateDigit(DIGITF, nibble);
    // nibble = score2/10;
    // updateDigit(DIGITG, nibble);
    // nibble = score2%10;
    // updateDigit(DIGITH, nibble);
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
    printNumArrays();
    // printLedArraysValues();

    dumpTable(ledTableValues, "ledTableValues");

    scoresReset();
    updateScores();
    dumpTable(ledTableValues, "ledTableValues");

    scoresPlus();
    updateScores();
    dumpTable(ledTableValues, "ledTableValues");

    // scoresPlus();
    // updateScores();
    // dumpTable(ledTableValues, "ledTableValues");

    // scoresSide();

    // scoresPlus();
    // updateScores();
    // dumpTable(ledTableValues, "ledTableValues");

    // scoresPlus();
    // updateScores();
    // dumpTable(ledTableValues, "ledTableValues");

    // scoresMinus();
    // updateScores();
    // dumpTable(ledTableValues, "ledTableValues");

    // scoresReset();
    // updateScores();
    // dumpTable(ledTableValues, "ledTableValues");
}

