#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

// helper functions
char sign(int i) { return i<0?0:1; }

#define True 0x01
#define False 0x00
typedef char bool;

typedef struct {
    size_t size;
    int ** board;
} board;

typedef struct {
    bool isRow; // true means its a horizontal move, false means its a vertical move
    int rowIndex; // what row or col to move
    int count; // the number of moves
} move;

void initLoopEngine() {
    srand(time(0)*999999999999999); // intialize random number generator
}

board createBoard(size_t size) {
    // initialize board
    board b;
    b.size = size;
    b.board = calloc(size, sizeof(int * ));

    //fill board
    for (int i = 0; i < size; i++) {
        int * row = calloc(size, sizeof(int));
        for (int j = 0; j < size; j++) {
            row[j] = i * size + j + 1;
        }
        b.board[i] = row;
    }

    return b;
}

void printBoard(board B) {
    for (int i = 0; i < B.size; i++) {
        for (int j = 0; j < B.size; j++) {
            int cell = B.board[i][j];
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

void printMove(move M) {
    printf("%d", M.count);

    if (M.isRow) {
        printf("R");
    } else {
        printf("C");
    }

    printf("%d\n", M.rowIndex);
}

bool randomBool() {
    if ((float)(rand())/RAND_MAX > 0.5) {
        return True;
    } else {
        return False;
    }
}

move getRandomMove(size_t maxCount) {
    move rmove;
    rmove.isRow = randomBool();
    rmove.rowIndex = ceil((float)(rand()) / RAND_MAX * (maxCount));

    if (randomBool()) {
        rmove.count = ceil((float)(rand()) / RAND_MAX * (maxCount/2+1));
    } else {
        rmove.count = -ceil((float)(rand()) / RAND_MAX * (maxCount/2+1));
    }

    return rmove;
}

void moveHorizontal(board* B, unsigned int row, bool toTheRight) {
    if (toTheRight) { // move to the right
        int temp = B -> board[row - 1][B -> size - 1];
        for (int i = B -> size - 1; i > 0; i--)
            B -> board[row - 1][i] = B -> board[row - 1][i - 1];
        B -> board[row - 1][0] = temp;
    }

    else { //move to the left
        int temp = B -> board[row - 1][0];
        for (int i = 0; i < B -> size - 1; i++)
            B -> board[row - 1][i] = B -> board[row - 1][i + 1];
        B -> board[row - 1][B -> size - 1] = temp;
    }
}

void moveVertical(board* B, unsigned int col, bool up) {
    if (up) { // move up
        int temp = B -> board[0][col - 1];
        for (int i = 0; i < B -> size - 1; i++)
            B -> board[i][col - 1] = B -> board[i + 1][col - 1];
        B -> board[B -> size - 1][col - 1] = temp;
    }

    else { //move down
        int temp = B -> board[B -> size - 1][col - 1];
        for (int i = B -> size - 1; i > 0; i--)
            B -> board[i][col - 1] = B -> board[i - 1][col - 1];
        B -> board[0][col - 1] = temp;
    }
}

void applyMove(board* B, move M) {
    if (M.isRow) {
        for (int i = 0; i < abs(M.count); i++) {
            moveHorizontal(B, M.rowIndex, sign(M.count));
        }
    }

    else {
        for (int i = 0; i < abs(M.count); i++) {
            moveVertical(B, M.rowIndex, sign(M.count));
        }
    }
};

void scrambleRandomMoves(board* B, unsigned int count) {
    for (unsigned int i = 0; i < count; i++)
        applyMove(B, getRandomMove(B->size));
}

// -----solving methods-----
typedef struct{
    unsigned int x;
    unsigned int y;
} location;

location locateNumber(unsigned int number, board* B){
    location ret;
    for (unsigned int y = 0; y < B->size; y++){
        for (unsigned int x = 0; x < B->size; x++){
            if (B->board[y][x] == number){
                ret.x = x;
                ret.y = y;
                return ret;
            }
        }
    }

    printf("error, cant locate number %d", number);
    exit(1);
}

void solveInsertion(board* B) {
    puts("solving first row");
    location tile = locateNumber(1, B);

    printf("tile one is at x = %d y = %d", tile.x, tile.y);
}

void solveWillems();
void solveImperial();