#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#ifndef LOOPOVER_H
#define LOOPOVER_H

#define True 0x01
#define False 0x00
typedef char bool;

typedef struct {
    size_t size;
    int* board;
} Board;

typedef struct {
    bool isRow; // true means its a horizontal move, false means its a vertical move
    int rowIndex; // what row or col to move
    int count; // the number of moves
} Move;

bool sign(int i);

void initLoopEngine();

Board createBoard(int size);

void printBoardTopLeft(Board B);

void printBoard(Board B);

void printmove(Move M);

bool randomBool();

Move getRandomMove(size_t maxCount);

void setBoard(Board* B, unsigned int x, unsigned int y, unsigned int val);

// not sure what this is
unsigned int getBoard(Board* B, unsigned int x, unsigned int y);

void moveHorizontal(Board* B, unsigned int row, bool right);

void moveVertical(Board* B, unsigned int col, bool up);

void applyMove(Board* B, Move M);

void scrambleRandomMoves(Board* B, unsigned int count);

// -----solving methods-----
typedef struct{
    unsigned int x;
    unsigned int y;
} location;

location locateNumber(unsigned int number, Board* B);

unsigned int solveInsertion(Board* B);

#endif