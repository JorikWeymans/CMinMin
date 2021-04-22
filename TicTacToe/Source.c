#include <stdio.h> //printf
#include <stdlib.h> //system

#include "board.h"
int main()
{

	printf("Tic Tac Toe start\n");

	
	pBoard board = Board_Create();
	Board_SetPiece(board, 3, 3, Piece_E);
	Board_SetPiece(board, -1, 0, Piece_E);

	Board_SetPiece(board, 0, 2, Piece_E);
	
	Board_Print(board);
	
	int c;
	c = getchar();
	putchar(c);



	//***
	//* Releasing resources
	//***
	free(board);

	
	system("Pause");
	



	
	return 0;
}
