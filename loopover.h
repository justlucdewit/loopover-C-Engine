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
    int* board;
} board;

typedef struct {
    bool isRow; // true means its a horizontal move, false means its a vertical move
    int rowIndex; // what row or col to move
    int count; // the number of moves
} move;

void initLoopEngine() {
    srand(time(NULL)); // intialize random number generator
}

board createBoard(size_t size) {
    // initialize board
    board b;
    b.size = size;

    int* board = (int*) malloc(size * size * sizeof(int));
    
    b.board = board;

    //fill board
    int count = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            *(b.board+i*size+j) = ++count;
        }
    }

    return b;
}

void printBoard(board B) {
    for (int i = 0; i < B.size; i++) {
        for (int j = 0; j < B.size; j++) {
            int cell = *(B.board+i*B.size+j);
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

void setBoard(board* B, unsigned int x, unsigned int y, unsigned int val) {
    B->board[y * B->size + x] = val;
}

unsigned int getBoard(board* B, unsigned int x, unsigned int y) {

}

void moveHorizontal(board* B, unsigned int row, bool toTheRight) {
    if (toTheRight) { // move to the right
        int temp = B->board[(row - 1)  * B->size + B->size - 1];
        for (int i = B->size - 1; i > 0; i--)
            B->board[(row - 1) * B->size + i] = B->board[(row - 1) * B->size + i - 1];
        setBoard(B, 0, row-1, temp);
    }

    else { //move to the left
        int temp = B->board[(row - 1)  * B -> size];
        for (int i = 0; i < B -> size - 1; i++)
            B->board[(row - 1) * B->size + i] = B->board[(row - 1) * B->size + i+1];
        setBoard(B, B->size-1, row-1, temp);
    }
}


void moveVertical(board* B, unsigned int col, bool up) {
    if (up) { // move up
        int temp = B->board[col - 1];
        for (int i = 0; i < B->size - 1; i++)
            B->board[i * B->size + (col - 1)] = B->board[(i+1) * B->size + (col - 1)];
        setBoard(B, col - 1, B->size - 1, temp);
    }

    else { //move down
        int temp = B->board[(col - 1) + (B->size-1)*B->size];
        for (int i = B -> size - 1; i > 0; i--)
            B->board[i * B->size + col - 1] = B->board[(i-1) * B->size + col - 1];
        setBoard(B, col-1, 0, temp);
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
    for (unsigned int i = 0; i < B->size*B->size; i++){
        if (B->board[i] == number){
            ret.x = i % B->size;
            ret.y = ceil(i/B->size);
            return ret;
        }
    }


    printf("error, cant locate number %d", number);
    puts("");
    printBoard(*B);
    exit(1);
}

unsigned int solveInsertion(board* B) {
    unsigned int moveCount = 0;

    // first row
    for (unsigned int tileNum = 1; tileNum < B->size; tileNum++) {
        location tile = locateNumber(tileNum, B);

        // move downward if already in row 1
        if (tileNum != 1 && tile.y == 0 && tile.x != tileNum-1) {
            moveVertical(B, tile.x+1, False);
            tile = locateNumber(tileNum, B);
        }
        
        // skip if already in place
        if (tile.y == 0 && tile.x == tileNum-1) {
            continue;
        }

        // move to the right x position
        while(tile.x != tileNum-1) {
            moveHorizontal(B, tile.y+1, (tile.x-tileNum-1) % B->size < B->size/2 ? False : True);
            tile = locateNumber(tileNum, B);
            moveCount++;
        }

        // move up or down to row 1
        while(tile.y != 0) {
            moveVertical(B, tile.x+1, tile.y > floor(B->size/2) ? False : True);
            tile = locateNumber(tileNum, B);
            moveCount++;

        }
    }
    
    return moveCount;
}