#include "loopover.h"

// gcc -O3 -march=native -lm -o main loopover.c main.c

int main() {
    initLoopEngine();

    Board B = createBoard(5);
    unsigned int avg = 0;
    unsigned int solvecount = 1000;
    for (unsigned int i = 0; i < solvecount; i++){
        scrambleRandomMoves(&B, 1000);
        printBoard(B);
        printf("\n");
        unsigned int movecount = solveInsertion(&B);
        printBoard(B);
        printf("solve %d took %d moves\n", i + 1, movecount);
        avg += movecount;
    }
    printf("avg moves: %f moves\n", (double)avg / solvecount);
    
    return 0;
}