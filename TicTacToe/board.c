#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define BUFFER_COUNT 41



BoardPiece CountTOBoardPiece(int count)
{
	if (count == Piece_X * BOARD_ROW_SIZE)
	{
		return Piece_X;
	}

	if (count == Piece_O * BOARD_ROW_SIZE)
	{
		return Piece_O;
	}

	return Piece_E;
}

const char* BoardPiece_ToString(BoardPiece data)
{
	switch (data)
	{
	case Piece_E: return "E";
	case Piece_X: return "X";
	case Piece_O: return "O";
	default: ; }

	return "_";
}
BoardPtr Board_Create()
{
	BoardPtr board = (struct Board*)malloc(sizeof(struct Board));

	if(board == NULL) return NULL;


	for(int i = 0; i < BOARD_SIZE; i++)
	{
		board->pieces[i] = Piece_E;
	}
	
	board->state = BoardState_Playing;
	board->winner = Piece_E;
	


	
	return board;
}
void Board_Print(BoardPtr board)
{
	char buffer[BUFFER_COUNT +1];
	
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
			bufferPos += sprintf_s(buffer + bufferPos, BUFFER_COUNT - bufferPos, "O|");
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

int Board_CoordinatesToIndex(int x, int y)
{
	if (x > 2 || x < 0 || y > 2 || y < 0)
	{
		return -1;
	}
	
	return (x % BOARD_ROW_SIZE) + (BOARD_ROW_SIZE * y);
}
bool SpaceIsFree(BoardPtr board, int x, int y)
{
	BoardPiece piece = board->pieces[Board_CoordinatesToIndex(x, y)];
	return (piece == Piece_E) ? true : false;
}
bool Board_SetPiece(BoardPtr board, int x, int y, BoardPiece data)
{
	int index = Board_CoordinatesToIndex(x, y);
	if(index == -1)
	{
		printf_s("[Board_SetPiece] the value of x and y should be between 0 and 2!\n");
		return false;
	}

	if(SpaceIsFree(board, x, y) == true)
	{
		board->pieces[index] = data;
		
		return true;
	}
	return false;

}

BoardPiece Board_CheckRow(BoardPtr board, int index)
{
	int count = 0;
	for(int i = 0; i < BOARD_ROW_SIZE; i++)
	{
		//printf_s("The piece is: %s\n", BoardPiece_ToString(board->pieces[thisIndex]));
		count += board->pieces[Board_CoordinatesToIndex(i, index)];
		
	}
	return CountTOBoardPiece(count);
}
BoardPiece Board_CheckCol(BoardPtr board, int index)
{
	int count = 0;
	for (int i = 0; i < BOARD_ROW_SIZE; i++)
	{
		//printf_s("The piece is: %s\n", BoardPiece_ToString(board->pieces[thisIndex]));
		count += board->pieces[Board_CoordinatesToIndex(index, i)];
	}
	return CountTOBoardPiece(count);

}
BoardPiece Board_CheckDia(BoardPtr board, bool counterDia)
{
	int count = 0;
	
	if(counterDia == false)
	{
		count += board->pieces[Board_CoordinatesToIndex(0, 0)];
		count += board->pieces[Board_CoordinatesToIndex(1, 1)];
		count += board->pieces[Board_CoordinatesToIndex(2, 2)];

		return CountTOBoardPiece(count);

	}

	count += board->pieces[Board_CoordinatesToIndex(2, 0)];
	count += board->pieces[Board_CoordinatesToIndex(1, 1)];
	count += board->pieces[Board_CoordinatesToIndex(2, 0)];
	
	return CountTOBoardPiece(count);
}
bool Board_CheckBoardState(BoardPtr board)
{
	BoardPiece winner = Piece_E;

	for(int i = 0; i < BOARD_ROW_SIZE; i++)
	{
		winner = Board_CheckRow(board, i);
		if(winner != Piece_E)
		{
			goto winnerFound;
		}
		winner = Board_CheckCol(board, i);
		if (winner != Piece_E)
		{
			goto winnerFound;
		}
		
	}

	winner = Board_CheckDia(board, false);
	if (winner != Piece_E)
	{
		goto winnerFound;

	}

	winner = Board_CheckDia(board, true);
	if (winner != Piece_E)
	{
		goto winnerFound;
	}

	
	return false;
	
	winnerFound:
	{
		board->winner = winner;
		board->state = BoardState_Finished;
		return true;
	}
	
	
}
