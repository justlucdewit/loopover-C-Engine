#include "loopover.h"

// helper functions
bool sign(int i) { return i>0; }

void initLoopEngine() {
    srand(time(NULL)); // intialize random number generator
}

Board createBoard(int size){
    // initialize board
    Board b;
    b.size = size;

    int* board = malloc(size * size * sizeof(int));
    
    b.board = board;

    //fill board
    int count = 0;
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            *(b.board + y * size + x) = ++count;
        }
    }

    return b;
}

void printBoardTopLeft(Board B){
    printf("%d\n", B.board[0]);
}

void printBoard(Board B) {
    for (int y = 0; y < B.size; y++) {
        for (int x = 0; x < B.size; x++) {
            int cell = *(B.board + y * B.size + x);
            printf("%d ", cell);

            if (B.size > 3 && cell < 10) {
                printf(" ");
            }

            if (B.size > 10 && cell < 100) {
                printf(" ");
            }

            if (B.size > 31 && cell < 1000) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void printMove(Move M) {
    printf("%d", M.count);

    if (M.isRow) {
        printf("R");
    } else {
        printf("C");
    }

    printf("%d\n", M.rowIndex);
}

bool randomBool() {
    return ((float) rand()) / RAND_MAX > 0.5;
}

Move getRandomMove(size_t maxCount) {
    Move rmove;
    rmove.isRow = randomBool();
    rmove.rowIndex = ceil(((float) rand()) / RAND_MAX * maxCount);
    rmove.count = ceil(((float) rand()) / RAND_MAX * (maxCount / 2 + 1));

    if (!randomBool()) {
        rmove.count *= -1;
    }

    return rmove;
}

void setBoard(Board* B, unsigned int x, unsigned int y, unsigned int val) {
    B->board[y * B->size + x] = val;
}

unsigned int getBoard(Board* B, unsigned int x, unsigned int y) {

}

void moveHorizontal(Board* B, unsigned int row, bool right) {
    if (right) { // move to the right
        // printf("move right\n");
        int temp = B->board[row * B->size - 1];
        for (int i = B->size - 1; i > 0; i--)
            B->board[(row - 1) * B->size + i] = B->board[(row - 1) * B->size + i - 1];
        setBoard(B, 0, row - 1, temp);
    } else { //move to the left
        // printf("move left\n");
        int temp = B->board[(row - 1)  * B->size];
        for (int i = 0; i < B->size - 1; i++)
            B->board[(row - 1) * B->size + i] = B->board[(row - 1) * B->size + i + 1];
        setBoard(B, B->size-1, row-1, temp);
    }
}


void moveVertical(Board* B, unsigned int col, bool up) {
    if (up) { // move up
        // printf("move up\n");
        int temp = B->board[col - 1];
        for (int i = 0; i < B->size - 1; i++)
            B->board[i * B->size + col - 1] = B->board[(i + 1) * B->size + col - 1];
        setBoard(B, col - 1, B->size - 1, temp);
    } else { //move down
        // printf("move down\n");
        int temp = B->board[col - 1 + (B->size - 1) * B->size];
        for (int i = B->size - 1; i > 0; i--)
            B->board[i * B->size + col - 1] = B->board[(i - 1) * B->size + col - 1];
        setBoard(B, col - 1, 0, temp);
    }
}


void applyMove(Board* B, Move M) {
    if (M.isRow) {
        for (int i = 0; i < abs(M.count); i++)
            moveHorizontal(B, M.rowIndex, sign(M.count));
    } else {
        for (int i = 0; i < abs(M.count); i++)
            moveVertical(B, M.rowIndex, sign(M.count));
    }
};

void scrambleRandomMoves(Board* B, unsigned int count) {
    for (unsigned int i = 0; i < count; i++)
        applyMove(B, getRandomMove(B->size));
}

// -----solving methods-----

location locateNumber(unsigned int number, Board* B){
    location ret;
    for (unsigned int i = 0; i < B->size * B->size; i++){
        if (B->board[i] == number){
            ret.x = i % B->size;
            ret.y = i / B->size;
            return ret;
        }
    }


    printf("error, cant locate number %d", number);
    puts("");
    printBoard(*B);
    exit(1);
}

unsigned int solveInsertion(Board* B) {
    unsigned int moveCount = 0;

    // first row
    for (unsigned int tileNum = 1; tileNum < B->size; tileNum++) {
        location tile = locateNumber(tileNum, B);

        // skip if already in place
        if (tile.y == 0 && tile.x == tileNum - 1) {
            continue;
        }

        // printf("%d ", tileNum);

        // move downward if already in row 1
        if (tileNum != 1 && tile.y == 0 && tile.x != tileNum - 1) {
            moveVertical(B, tile.x + 1, False);
            tile.y++;
            moveCount++;
        }

        // move to the right x position
        while (tile.x != tileNum - 1) {
            moveHorizontal(B, tile.y + 1, (tile.x - (tileNum - 1)) % B->size >= B->size / 2);
            tile = locateNumber(tileNum, B);
            moveCount++;
        }

        // move up or down to row 1
        while(tile.y != 0) {
            moveVertical(B, tile.x + 1, tile.y < B->size / 2);
            tile = locateNumber(tileNum, B);
            moveCount++;
        }
    }
    
    return moveCount;
}