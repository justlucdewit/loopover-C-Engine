#include "loopover.h"

int main() {
    initLoopEngine();

    board B = createBoard(5);
    scrambleRandomMoves(&B, 1000);
    solveInsertion(&B);
    puts("\n");
    printBoard(B);

    return 0;
}