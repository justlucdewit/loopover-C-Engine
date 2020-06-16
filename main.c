#include "loopover.h"

int main() {
    initLoopEngine();

    board B = createBoard(2);
    unsigned int avg = 0;
    unsigned int solvecount = 500;
    for (unsigned int i = 0; i < solvecount; i++){
	    scrambleRandomMoves(&B, 1000);
	    unsigned int movecount = solveInsertion(&B);
	    //printBoard(B);
	    printf("solve %d took %d moves\n", i+1, movecount);
	    avg += movecount;
	}
	printf("avg moves: %f moves\n", (double)avg / solvecount);
	
    return 0;
}