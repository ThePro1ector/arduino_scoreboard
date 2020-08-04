
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// gcc scoreboard.c -o runme ; ./runme

// C version to test ideas faster without loading on Arduino

#define C_APP
// #define INO_APP

//setup
// - turn all leds off
// - set counts A,B and (if double sided) C,D to "00 00"
// - set count A brigher indicating side (serving)

#define LEDS_PER_ROW 15
#define LED_ROWS 5
#define LED_SIDES 2


bool sideA = true;
int scoreA = 0;
int scoreB = 0;
int op = ' ';
bool running = true;


void usage() {
    printf("options\n");
    printf("  r - reset scores\n");
    printf("  s - side-active change\n");
    printf("  p - add to side-active score\n");
    printf("  m - subtract to side-active score\n");
}

void get_op() {
#ifdef C_APP
    printf("option: ");
    op = getchar();
#endif
}

void clr_op() {
#ifdef C_APP
    getchar();
#endif
}


#ifdef C_APP

#define COLS (2*15)
#define ROWS 5
#define SIDES 2
#define DIGIT_WIDTH 3
#define DIGIT_GAP 0
#define SCORE_GAP 3

void print_table() {
    int i, side, cols, col, row, index;

    // verify columns
    cols = SIDES * (4*DIGIT_WIDTH + 2*DIGIT_GAP + SCORE_GAP);
    if (cols != COLS) {
        printf("WARNING: estimated col (%d) != COL (%d)\n", cols, COLS);
    }

    // start top,left
    printf("int table[%d][%d] = [\n", ROWS, COLS);
    index = 0;
    for (row = 0; row < ROWS; row++) {
        col = 0;
        printf("  [ ");
        for (side = 0; side < SIDES; side++) {
            for (i=0; i<DIGIT_WIDTH; i++) {
                printf("%03d, ", index);
                col++;
                index++;
            }
            for (i=0; i<DIGIT_GAP; i++) {
                printf(" ");
                col++;
                index++;
            }
            for (i=0; i<DIGIT_WIDTH; i++) {
                printf("%03d, ", index);
                col++;
                index++;
            }
            for (i=0; i<SCORE_GAP; i++) {
                printf(" ");
                col++;
                index++;
           }
            for (i=0; i<DIGIT_WIDTH; i++) {
                printf("%03d, ", index);
                col++;
                index++;
            }
            for (i=0; i<DIGIT_GAP; i++) {
                printf(" ");
                col++;
                index++;
            }
            for (i=0; i<DIGIT_WIDTH; i++) {
                printf("%03d", index);
                if ((col+1) < COLS) printf(", ");
                else                  printf(" ");
                col++;
                index++;
            }
            if ((side+1) < SIDES) printf("     ");
        }
        printf("]");
        if ((row+1) < ROWS) printf(",");
        printf("\n");
    }
    printf("];\n");


    // start bottom,right
    printf("int table[%d][%d] = [\n", ROWS, COLS);
    index = (ROWS * COLS) -1;
    for (row = 0; row < ROWS; row++) {
        col = 0;
        printf("  [ ");
        for (side = 0; side < SIDES; side++) {
            for (i=0; i<DIGIT_WIDTH; i++) {
                printf("%03d, ", index);
                col++;
                index--;
            }
            for (i=0; i<DIGIT_GAP; i++) {
                printf(" ");
                col++;
                index--;
            }
            for (i=0; i<DIGIT_WIDTH; i++) {
                printf("%03d, ", index);
                col++;
                index--;
            }
            for (i=0; i<SCORE_GAP; i++) {
                printf(" ");
                col++;
                index--;
           }
            for (i=0; i<DIGIT_WIDTH; i++) {
                printf("%03d, ", index);
                col++;
                index--;
            }
            for (i=0; i<DIGIT_GAP; i++) {
                printf(" ");
                col++;
                index--;
            }
            for (i=0; i<DIGIT_WIDTH; i++) {
                printf("%03d", index);
                if ((col+1) < COLS) printf(", ");
                else                  printf(" ");
                col++;
                index--;
            }
            if ((side+1) < SIDES) printf("     ");
        }
        printf("]");
        if ((row+1) < ROWS) printf(",");
        printf("\n");
    }
    printf("];\n");
}
#endif // C_APP

void print_txt() {
    printf("%s %02d  %02d %s\n", 
        (sideA ? ">" : " "),
        scoreA,
        scoreB,
        (sideA ? " " : "<")
    );
}


void setup() {
}

void loop() {
    get_op();
    switch (op) {
        case 'r': {
            scoreA = 0;
            scoreB = 0;
            }
            break;
        case 's':
            sideA = !sideA;
            break;
        case 'p':
            if (sideA) { scoreA += 1; }
            else       { scoreB += 1; }
            break;
        case 'm': {
            if (sideA) { scoreA -= 1; }
            else       { scoreB -= 1; }
            if (scoreA < 0) { scoreA = 0; }
            if (scoreB < 0) { scoreB = 0; }
            }
#ifdef C_APP
        case '?' :
        case 'h' :
            usage();
            break;
        case 'q' :
            running = false;
            break;
        case 't':
            print_table();
            break;
#endif
    }
    clr_op();
    print_txt();
}

//////////////////////////////////////////////////////
// Main
//////////////////////////////////////////////////////
int main(void) {

    setup();

    while (running) {
        loop();
    }
    return 0;
}