
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// generate.c
// This application accepts a template file and inserts a set of tables

// to build and run, use the following:
// rm -f ./runme ; gcc generate.c -o runme ; ./runme

// TODO: read these from a config file

#define TOP_RIGHT       1
#define START_LED       0
#define COLS            (2*15)
#define ROWS            5
#define SIDES           2  // NOTE: cannot change yet
#define DIGIT_WIDTH     3
#define DIGIT_GAP       0
#define SCORE_GAP       3
#define MAX_SCORE       99

#define DIGITA  0
#define DIGITB  1
#define DIGITC  2
#define DIGITD  3
#define DIGITE  4
#define DIGITF  5
#define DIGITG  6
#define DIGITH  7
#define DIGITS  8


void dumpTable(FILE *fp, int table[ROWS][COLS], char *name) {
    int col, row;
    fprintf(fp, "int %s[ROWS][COLS] = {\n", name);
    for (row = 0; row < ROWS; row++) {
        fprintf(fp, "  {");
        for (col = 0; col < COLS; col++) {
            if (col == COLS/2) fprintf(fp, "     ");
            if ((col+1) < COLS) fprintf(fp, "%3d,", table[row][col]);
            else                fprintf(fp, "%3d", table[row][col]);
        }
        if ((row+1) < ROWS) fprintf(fp, "},\n");
        else                fprintf(fp, "}\n");
    }
    fprintf(fp, "};\n");
}

void dumpDigitsArray(FILE *fp, int digits[DIGITS][ROWS][DIGIT_WIDTH], char *name) {
    int col, row, digit;
    fprintf(fp, "int %s[DIGITS][ROWS][DIGIT_WIDTH] = {\n", name);
    for (digit = 0; digit < DIGITS; digit++) {
        fprintf(fp, "{\n");
         for (row = 0; row < ROWS; row++) {
            fprintf(fp, "  {");
            for (col = 0; col < DIGIT_WIDTH; col++) {
                if ((col+1) < DIGIT_WIDTH) fprintf(fp, "%3d,", digits[digit][row][col]);
                else                fprintf(fp, "%3d ", digits[digit][row][col]);
            }
            if ((row+1) < ROWS) fprintf(fp, "},\n");
            else                fprintf(fp, "}\n");
        }
        fprintf(fp, "},\n");
    }
    fprintf(fp, "};\n");
}

void dumpNumArray(FILE *fp, int digit[ROWS][DIGIT_WIDTH]) {
    int col, row;
    fprintf(fp, "{\n");
    for (row = 0; row < ROWS; row++) {
        fprintf(fp, "  {");
        for (col = 0; col < DIGIT_WIDTH; col++) {
            if ((col+1) < DIGIT_WIDTH) fprintf(fp, "%3d,", digit[row][col]);
            else                fprintf(fp, "%3d ", digit[row][col]);
        }
        if ((row+1) < ROWS) fprintf(fp, "},\n");
        else                fprintf(fp, "}\n");
    }
    fprintf(fp, "},\n");
}



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

void printLedArrays(FILE *fp) {
    int i, side, cols, col, row, index;
    int table[ROWS][COLS];
    int tableValues[ROWS][COLS];
    int digits[DIGITS][ROWS][DIGIT_WIDTH];

    clearTable(table, -1);
#if TOP_RIGHT == 1
    // start top,left
    index = START_LED;
    if (START_LED == -1) index = 0;
    for (row = 0; row < ROWS; row++) {
        col = 0;
        for (i=0; i<DIGIT_WIDTH; i++) {
            table[row][col] = index;
            digits[DIGITA][row][i] = index;
            col++;
            index++;
        }
        for (i=0; i<DIGIT_GAP; i++) {
            col++;
            index++;
        }
        for (i=0; i<DIGIT_WIDTH; i++) {
            table[row][col] = index;
            digits[DIGITB][row][i] = index;
            col++;
            index++;
        }
        for (i=0; i<SCORE_GAP; i++) {
            col++;
            index++;
        }
        for (i=0; i<DIGIT_WIDTH; i++) {
            table[row][col] = index;
            digits[DIGITC][row][i] = index;
            col++;
            index++;
        }
        for (i=0; i<DIGIT_GAP; i++) {
            col++;
            index++;
        }
        for (i=0; i<DIGIT_WIDTH; i++) {
            table[row][col] = index;
            digits[DIGITD][row][i] = index;
            col++;
            index++;
        }
        for (i=0; i<DIGIT_WIDTH; i++) {
            table[row][col] = index;
            digits[DIGITE][row][i] = index;
            col++;
            index++;
        }
        for (i=0; i<DIGIT_GAP; i++) {
            col++;
            index++;
        }
        for (i=0; i<DIGIT_WIDTH; i++) {
            table[row][col] = index;
            digits[DIGITF][row][i] = index;
            col++;
            index++;
        }
        for (i=0; i<SCORE_GAP; i++) {
            col++;
            index++;
        }
        for (i=0; i<DIGIT_WIDTH; i++) {
            table[row][col] = index;
            digits[DIGITG][row][i] = index;
            col++;
            index++;
        }
        for (i=0; i<DIGIT_GAP; i++) {
            col++;
            index++;
        }
        for (i=0; i<DIGIT_WIDTH; i++) {
            table[row][col] = index;
            digits[DIGITH][row][i] = index;
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
            digits[DIGITA][row][i] = index;
            col++;
            index--;
        }
        for (i=0; i<DIGIT_GAP; i++) {
            col++;
            index--;
        }
        for (i=0; i<DIGIT_WIDTH; i++) {
            table[row][col] = index;
            digits[DIGITB][row][i] = index;
            col++;
            index--;
        }
        for (i=0; i<SCORE_GAP; i++) {
            col++;
            index--;
        }
        for (i=0; i<DIGIT_WIDTH; i++) {
            table[row][col] = index;
            digits[DIGITC][row][i] = index;
            col++;
            index--;
        }
        for (i=0; i<DIGIT_GAP; i++) {
            col++;
            index--;
        }
        for (i=0; i<DIGIT_WIDTH; i++) {
            table[row][col] = index;
            digits[DIGITD][row][i] = index;
            col++;
            index--;
        }
        for (i=0; i<DIGIT_WIDTH; i++) {
            table[row][col] = index;
            digits[DIGITE][row][i] = index;
            col++;
            index--;
        }
        for (i=0; i<DIGIT_GAP; i++) {
            col++;
            index--;
        }
        for (i=0; i<DIGIT_WIDTH; i++) {
            table[row][col] = index;
            digits[DIGITF][row][i] = index;
            col++;
            index--;
        }
        for (i=0; i<SCORE_GAP; i++) {
            col++;
            index--;
        }
        for (i=0; i<DIGIT_WIDTH; i++) {
            table[row][col] = index;
            digits[DIGITG][row][i] = index;
            col++;
            index--;
        }
        for (i=0; i<DIGIT_GAP; i++) {
            col++;
            index--;
        }
        for (i=0; i<DIGIT_WIDTH; i++) {
            table[row][col] = index;
            digits[DIGITH][row][i] = index;
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

    fprintf(fp, "// This table is used to inspect how the led string is layed out as digits\n");
    fprintf(fp, "//#ifdef INSPECTION\n");
    dumpTable(fp, table, "ledTable");
    fprintf(fp, "#endif // INSPECTION\n");

    fprintf(fp, "// This table is used display the simulated led table\n");
    fprintf(fp, "//#ifdef SIMULATED\n");
    dumpTable(fp, tableValues, "ledTableValues");
    fprintf(fp, "#endif // SIMULATED\n");

    fprintf(fp, "// This table is a map of digits to leds\n");
    fprintf(fp, "//   side1 -  side2  \n");
    fprintf(fp, "//   00 00 -  00 00  \n");
    fprintf(fp, "//   AB CD -  EF GH  \n");
     dumpDigitsArray(fp, digits, "ledDigitsArray");

    // verify columns
    cols = SIDES * (2*(DIGIT_WIDTH+DIGIT_WIDTH) + 2*DIGIT_GAP + SCORE_GAP);
    if (cols != COLS) {
        fprintf(fp, "WARNING: estimated col (%d) != COL (%d)\n", cols, COLS);
    }
}


void setSegments(int numArray[ROWS][DIGIT_WIDTH], int seg1, int seg2, int seg3, int seg4, int seg5, int seg6, int seg7) {
    int i, temp;
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

void printNumArrays(FILE *fp) {
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

    fprintf(fp, "// This table is a map of nibbles (0-9) to digits, specifically which leds are on/off\n");
    fprintf(fp, "int numArrays[10][ROWS][DIGIT_WIDTH] = {\n");
    dumpNumArray(fp, num0);
    dumpNumArray(fp, num1);
    dumpNumArray(fp, num2);
    dumpNumArray(fp, num3);
    dumpNumArray(fp, num4);
    dumpNumArray(fp, num5);
    dumpNumArray(fp, num6);
    dumpNumArray(fp, num7);
    dumpNumArray(fp, num8);
    dumpNumArray(fp, num9);
    fprintf(fp, "};\n");

}


////////////////////////////////////////////////////////////////////////////////
// Main
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]) {
    int i;
    long fileSize, numRead;
    char *buffer, *mark1, *mark2;
    FILE *fp;

    if (argc != 2) {
        printf("ERROR: please provide a template file name.\n");
        exit(1);
    }
    fp = fopen(argv[1], "r");
    if (!fp) {
        printf("ERROR: please provide a valid template file name.\n");
        exit(1);
    }

    // find size of file
    fseek(fp, 0, SEEK_END);
    fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // allocate buffer
    buffer = (char *)malloc(fileSize);
    if (!buffer) {
        fclose(fp);
        printf("ERROR: could not allocate buffer to read file.\n");
        exit(1);
    }
    numRead = fread(buffer, 1, fileSize, fp);
    fclose(fp);

    // validate number read
    if (numRead != fileSize) {
        printf("ERROR: failed to read file.\n");
        exit(1);
    }

    // find markers
    mark1 = strstr(buffer, "// GENERATED CODE BELOW");
    mark2 = strstr(buffer, "// GENERATED CODE ABOVE");
    if (!mark1) {
        printf("ERROR: failed to find marker '// GENERATED CODE BELOW'.\n");
        exit(1);
    }
    if (!mark2) {
        printf("ERROR: failed to find marker '// GENERATED CODE ABOVE'.\n");
        exit(1);
    }
    mark1 += strlen("// GENERATED CODE BELOW\n");

    // reopen file to write
    // fp = fopen(argv[1], "w");
    // if (!fp) {
    //     printf("ERROR: could not open '%s' to rewrite.\n", argv[1]);
    //     exit(1);
    // }


    // fclose(fp);
    free(buffer);

    // printLedArrays(fp);
    // printNumArrays(fp);


}

