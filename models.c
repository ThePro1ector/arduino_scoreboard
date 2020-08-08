
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


void printLedStripAsTable() {
    int i, side, cols, col, row, index;
    int maxScore = 0;

    // verify columns
    cols = SIDES * (2*(DIGIT_WIDTH_MSB+DIGIT_WIDTH_LSB) + 2*DIGIT_GAP + SCORE_GAP);
    if (cols != COLS) {
        printf("WARNING: estimated col (%d) != COL (%d)\n", cols, COLS);
    }
    

    printf("// #define TOP_RIGHT       %d\n", TOP_RIGHT);
    printf("// #define START_LED       %d\n", START_LED);
    printf("// #define COLS            %d\n", COLS);
    printf("// #define ROWS            %d\n", ROWS);
    printf("// #define SIDES           %d\n", SIDES);
    printf("// #define DIGIT_WIDTH_MSB %d\n", DIGIT_WIDTH_MSB);
    printf("// #define DIGIT_WIDTH_LSB %d\n", DIGIT_WIDTH_LSB);
    printf("// #define DIGIT_GAP       %d\n", DIGIT_GAP);
    printf("// #define SCORE_GAP       %d\n", SCORE_GAP);
    if (DIGIT_WIDTH_MSB >= 3 && DIGIT_WIDTH_LSB >= 3) maxScore = 99;
    else if (DIGIT_WIDTH_MSB == 1 && DIGIT_WIDTH_LSB >= 3) maxScore = 19;
    printf("// #define MAX_SCORE       %d\n", maxScore);
    printf("\n");

#if TOP_RIGHT == 1
    // start top,left
    printf("int ledStripAsTable[%d][%d] = {\n", ROWS, COLS);
    index = START_LED;
    if (START_LED == -1) index = 0;
    for (row = 0; row < ROWS; row++) {
        col = 0;
        printf("  { ");
        for (side = 0; side < SIDES; side++) {
            for (i=0; i<DIGIT_WIDTH_MSB; i++) {
                printf("%3d, ", index);
                col++;
                index++;
            }
            for (i=0; i<DIGIT_GAP; i++) {
                printf("%3d, ", -1);
                col++;
                index++;
            }
            for (i=0; i<DIGIT_WIDTH_LSB; i++) {
                printf("%3d, ", index);
                col++;
                index++;
            }
            for (i=0; i<SCORE_GAP; i++) {
                printf("%3d, ", -1);
                col++;
                index++;
           }
            for (i=0; i<DIGIT_WIDTH_MSB; i++) {
                printf("%3d, ", index);
                col++;
                index++;
            }
            for (i=0; i<DIGIT_GAP; i++) {
                printf("%3d, ", -1);
                col++;
                index++;
            }
            for (i=0; i<DIGIT_WIDTH_LSB; i++) {
                printf("%3d", index);
                if ((col+1) < COLS) printf(", ");
                else                  printf(" ");
                col++;
                index++;
            }
            if ((side+1) < SIDES) printf("     ");
        }
        printf("}");
        if ((row+1) < ROWS) printf(",");
        printf("\n");
    }
    printf("};\n");
#endif // TOP_RIGHT=1


#if TOP_RIGHT == 0
    // start bottom,right
    printf("int ledStripAsTable[%d][%d] = {\n", ROWS, COLS);
    index = START_LED;
    if (START_LED == -1) index = (ROWS * COLS) -1;
     for (row = 0; row < ROWS; row++) {
        col = 0;
        printf("  { ");
        for (side = 0; side < SIDES; side++) {
            for (i=0; i<DIGIT_WIDTH_MSB; i++) {
                printf("%3d, ", index);
                col++;
                index--;
            }
            for (i=0; i<DIGIT_GAP; i++) {
                printf("%3d, ", -1);
                col++;
                index--;
            }
            for (i=0; i<DIGIT_WIDTH_LSB; i++) {
                printf("%3d, ", index);
                col++;
                index--;
            }
            for (i=0; i<SCORE_GAP; i++) {
                printf("%3d, ", -1);
                col++;
                index--;
           }
            for (i=0; i<DIGIT_WIDTH_MSB; i++) {
                printf("%3d, ", index);
                col++;
                index--;
            }
            for (i=0; i<DIGIT_GAP; i++) {
                printf("%3d, ", -1);
                col++;
                index--;
            }
            for (i=0; i<DIGIT_WIDTH_LSB; i++) {
                printf("%3d", index);
                if ((col+1) < COLS) printf(", ");
                else                  printf(" ");
                col++;
                index--;
            }
            if ((side+1) < SIDES) printf("     ");
        }
        printf("}");
        if ((row+1) < ROWS) printf(",");
        printf("\n");
    }
    printf("};\n");
#endif // TOP_RIGHT=1

    // verify columns
    cols = SIDES * (2*(DIGIT_WIDTH_MSB+DIGIT_WIDTH_LSB) + 2*DIGIT_GAP + SCORE_GAP);
    if (cols != COLS) {
        printf("WARNING: estimated col (%d) != COL (%d)\n", cols, COLS);
    }
}


void printLedStripAsTableValues() {
    int col, row;

    printf("int ledStripAsTableValues[%d][%d] = {\n", ROWS, COLS);
    for (row = 0; row < ROWS; row++) {
        printf("  { ");
        for (col = 0; col < COLS; col++) {
            if (SIDES == 2 && col == COLS/2) printf("     ");

            if ((col+1) < COLS) printf("%3d, ", 0);
            else                printf("%3d  ", 0);
        }
        printf("}");
        if ((row+1) < ROWS) printf(",");
        printf("\n");
    }
    printf("};\n");
}

void printDumpLedStripAsTableValues() {
    printf("void dumpLedStripAsTableValues() {\n");
    printf("    int col, row;\n");
    printf("    for (row = 0; row < ROWS; row++) {\n");
    printf("        for (col = 0; col < COLS; col++) {\n");
    if (SIDES == 2)
        printf("            if (col == COLS/2) printf(\"     \");\n");
    printf("            if ((col+1) < COLS) printf(\"%%3d,\", ledStripAsTableValues[row][col]);\n");
    printf("            else                printf(\"%%3d \", ledStripAsTableValues[row][col]);\n");
    printf("        }\n");
    printf("        printf(\"\\n\");\n");
    printf("    }\n");
    printf("}\n");

}

////////////////////////////////////////////////////////////////////////////////
// Main
////////////////////////////////////////////////////////////////////////////////
int main(void) {
    printLedStripAsTable();
    printLedStripAsTableValues();
    printDumpLedStripAsTableValues();
}

