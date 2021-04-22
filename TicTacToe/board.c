#include "board.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_COUNT 41

pBoard Board_Create()
{
	pBoard board = (struct Board*)malloc(sizeof(struct Board));

	if(board == NULL) return NULL;


	//Is going to be removed with an if structure
	board->pieces[0] = Piece_E;
	board->pieces[1] = Piece_E;
	board->pieces[2] = Piece_E;
	
	board->pieces[3] = Piece_O;
	board->pieces[4] = Piece_O;
	board->pieces[5] = Piece_O;

	board->pieces[6] = Piece_X;
	board->pieces[7] = Piece_X;
	board->pieces[8] = Piece_X;


	board->state = Sate_Playing;



	
	return board;
}
void Board_Print(pBoard board)
{
	char buffer[BUFFER_COUNT];
	
	int bufferPos = sprintf_s(buffer, BUFFER_COUNT, "   0 2 3\n0 |");
	
	int rowCount = 0;
	
	for(int i = 0; i < BOARD_SIZE; i++)
	{
		switch (board->pieces[i])
		{
		case Piece_E:
			bufferPos += sprintf_s(buffer + bufferPos, BUFFER_COUNT - bufferPos, " |");
			break;
		case Piece_X:
			bufferPos += sprintf_s(buffer + bufferPos, BUFFER_COUNT - bufferPos, "X|");
			break;
		case Piece_O:
			bufferPos += sprintf_s(buffer + bufferPos, BUFFER_COUNT - bufferPos, "0|");
			break;
		default:
			bufferPos += sprintf_s(buffer + bufferPos, BUFFER_COUNT - bufferPos, "ER");
		}
		
		if(i % BOARD_ROW_SIZE == 2 && i != BOARD_SIZE - 1)
		{
			rowCount++;
			bufferPos += sprintf_s(buffer + bufferPos, BUFFER_COUNT - bufferPos, "\n%i |", rowCount);
		}
	}
	
	sprintf_s(buffer + bufferPos, BUFFER_COUNT - bufferPos, "\n\n");
	printf_s(buffer);
	
	
}
void Board_SetPiece(pBoard board, int x, int y, BoardPiece data)
{
	if(x > 2 || x < 0|| y > 2 || y < 2)
	{
		printf_s("[Board_SetPiece] the value of x and y should be between 0 and 2!\n");
		return;
	}
	board->pieces[(x % BOARD_ROW_SIZE) + (BOARD_ROW_SIZE * y) ] = data;
}
