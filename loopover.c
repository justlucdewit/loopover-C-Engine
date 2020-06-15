#include <stdlib.h>
#include <stdio.h>

typedef struct{
	int size;
	int** board;
} board;

board createBoard(int size){
	// initialize board
	board b;
	b.size = size;
	b.board = calloc(size, sizeof(int*));

	//fill board
	for (int i = 0; i < size; i++){
		int* row = calloc(size, sizeof(int));
		for (int j = 0; j < size; j++){
			row[j] = i*size+j;
		}
		b.board[i] = row;
	}

	return b;
}

void printBoard(board B){
	printf("%d", B.board[0][0]);
}
