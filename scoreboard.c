
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// gcc scoreboard.c -o scoreboard ; ./scoreboard

// C version to test ideas faster without loading on Arduino


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


void usage(void) {
    printf("options\n");
    printf("  r - reset scores\n");
    printf("  s - side-active change\n");
    printf("  p - add to side-active score\n");
    printf("  m - subtract to side-active score\n");
}



void print_txt(void) {
    printf("%s %02d  %02d %s\n", 
        (sideA ? ">" : " "),
        scoreA,
        scoreB,
        (sideA ? " " : "<")
    );
}

//////////////////////////////////////////////////////
// Main
//////////////////////////////////////////////////////
int main(void) {
    bool running = true;
    char c;

    while (running) {
        printf("option: ");
        c = getchar();
        switch (c) {
            case '?' :
                usage();
                break;
            case 'q' :
                running = false;
                break;
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
                break;
        }
        getchar();
        print_txt();
    }
    return 0;
}