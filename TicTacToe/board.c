#include "board.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "utils.h"
#define BUFFER_COUNT 41

const char* BoardPiece_ToString(enum BoardPiece data)
{
	switch (data)
	{
	case Piece_E: return "E";
	case Piece_X: return "X";
	case Piece_O: return "O";
	default: ; }

	return "_";
}
struct Board* Board_Create()
{
	struct Board* pBoard = (struct Board*)malloc(sizeof(struct Board));

	if(pBoard == NULL) return NULL;


	for(int i = 0; i < BOARD_SIZE; i++)
	{
		pBoard->pieces[i] = Piece_E;
	}
	
	/* Testing pBoards
	//For Testing the AI
	//pBoard->pieces[Board_CoordinatesToIndex(0, 0)] = Piece_X;
	//pBoard->pieces[Board_CoordinatesToIndex(2, 1)] = Piece_X;
	//pBoard->pieces[Board_CoordinatesToIndex(2, 2)] = Piece_X;
	//
	//pBoard->pieces[Board_CoordinatesToIndex(2, 0)] = Piece_O;
	//pBoard->pieces[Board_CoordinatesToIndex(1, 2)] = Piece_O;
	//pBoard->pieces[Board_CoordinatesToIndex(0, 2)] = Piece_O;

	//pBoard->pieces[Board_CoordinatesToIndex(0, 0)] = Piece_X;
	//pBoard->pieces[Board_CoordinatesToIndex(0, 1)] = Piece_X;
	//pBoard->pieces[Board_CoordinatesToIndex(1, 1)] = Piece_X;
	//pBoard->pieces[Board_CoordinatesToIndex(2, 2)] = Piece_X;

	//pBoard->pieces[Board_CoordinatesToIndex(0, 2)] = Piece_O;
	//pBoard->pieces[Board_CoordinatesToIndex(1, 2)] = Piece_O;
	//pBoard->pieces[Board_CoordinatesToIndex(2, 1)] = Piece_O;	
	
	//pBoard->pieces[0] = Piece_X; pBoard->pieces[1] = Piece_O; pBoard->pieces[2] = Piece_X;
	//pBoard->pieces[3] = Piece_O; pBoard->pieces[4] = Piece_O; pBoard->pieces[5] = Piece_X;
	//pBoard->pieces[6] = Piece_E; pBoard->pieces[7] = Piece_E; pBoard->pieces[8] = Piece_E;
	
	//pBoard->pieces[0] = Piece_O; pBoard->pieces[1] = Piece_X; pBoard->pieces[2] = Piece_O;
	//pBoard->pieces[3] = Piece_X; pBoard->pieces[4] = Piece_X; pBoard->pieces[5] = Piece_O;
	//pBoard->pieces[6] = Piece_E; pBoard->pieces[7] = Piece_E; pBoard->pieces[8] = Piece_E;
	//

	//pBoard->pieces[0] = Piece_E; pBoard->pieces[1] = Piece_E; pBoard->pieces[2] = Piece_E;
	//pBoard->pieces[3] = Piece_X; pBoard->pieces[4] = Piece_O; pBoard->pieces[5] = Piece_E;
	//pBoard->pieces[6] = Piece_X; pBoard->pieces[7] = Piece_O; pBoard->pieces[8] = Piece_X;

	//pBoard->pieces[0] = Piece_E; pBoard->pieces[1] = Piece_E; pBoard->pieces[2] = Piece_E;
	//pBoard->pieces[3] = Piece_E; pBoard->pieces[4] = Piece_O; pBoard->pieces[5] = Piece_E;
	//pBoard->pieces[6] = Piece_X; pBoard->pieces[7] = Piece_X; pBoard->pieces[8] = Piece_E;

	//pBoard->pieces[0] = Piece_O; pBoard->pieces[1] = Piece_X; pBoard->pieces[2] = Piece_O;
	//pBoard->pieces[3] = Piece_O; pBoard->pieces[4] = Piece_X; pBoard->pieces[5] = Piece_E;
	//pBoard->pieces[6] = Piece_X; pBoard->pieces[7] = Piece_O; pBoard->pieces[8] = Piece_E;
	*/


	
	pBoard->state = BoardState_Playing;
	pBoard->winner = Piece_E;
	
	return pBoard;
}
struct Board* Board_Copy(struct Board const * original)
{
	struct Board* newBoard = Board_Create();
	if (newBoard == NULL) return NULL;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		newBoard->pieces[i] = original->pieces[i];
	}
	
	newBoard->state = original->state;
	newBoard->winner = original->winner;
	
	return newBoard;
}
void Board_Print(struct Board* pBoard)
{
	char buffer[BUFFER_COUNT +1];
	
	int bufferPos = sprintf_s(buffer, BUFFER_COUNT, "   0 1 2\n0 |");
	
	int rowCount = 0;
	
	for(int i = 0; i < BOARD_SIZE; i++)
	{
		switch (pBoard->pieces[i])
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
bool Board_SpaceIsFree(struct Board* pBoard, int x, int y)
{
	enum BoardPiece piece = pBoard->pieces[Board_CoordinatesToIndex(x, y)];
	return (piece == Piece_E) ? true : false;
}
bool Board_HasFreeSpace(struct Board* pBoard)
{
	for(int i = 0; i < BOARD_SIZE; i++)
	{
		if (pBoard->pieces[i] == Piece_E)
			return true;
	}
	return false;
}
bool Board_SetPiece(struct Board* pBoard, int x, int y, enum BoardPiece data)
{
	int index = Board_CoordinatesToIndex(x, y);
	if(index == -1)
	{
		printf_s("[Board_SetPiece] the value of x and y should be between 0 and 2!\n");
		return false;
	}

	if(Board_SpaceIsFree(pBoard, x, y) == true)
	{
		pBoard->pieces[index] = data;
		
		return true;
	}
	return false;

}
bool Board_SetPieceWithIndex(struct Board* pBoard, int index, enum BoardPiece data)
{
	if (index < 0 || index >= BOARD_SIZE)
	{
		printf_s("[Board_SetPieceWithIndex] the value of x and y should be between 0 and 2!\n");
		return false;
	}

	if (pBoard->pieces[index] == Piece_E)
	{
		pBoard->pieces[index] = data;

		return true;
	}
	if( data == Piece_E)
	{
		printf_s("[Board_SetPieceWithIndex] Use ClearPiece if you use Piece_E");
		return false;
	}
	
	return false;
}
void Board_ClearPieceWithIndex(struct Board* pBoard, int index)
{
	pBoard->pieces[index] = Piece_E;
}
IntArray Board_GetEmptyIndices(struct Board* pBoard)
{

	IntArray arr;
	arr.count = 0;
	arr.start = NULL;

	for(int i = 0; i < BOARD_SIZE; i++)
	{
		if (pBoard->pieces[i] == Piece_E)
			arr.count++;
	}

	if(arr.count <= 0)
	{
		return arr;
	}
	
	arr.start = (int*)malloc(sizeof(int) * arr.count);
	//Going over the loop again and now filling it
	int current = 0;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if (pBoard->pieces[i] == Piece_E)
		{
			arr.start[current] = i;
			current++;
		}
	}
	
	
	return arr;
}
int Board_GetNumberOfUsedSpots(struct Board* pBoard)
{
	int count = 0;

	for(int i = 0; i < BOARD_SIZE; i++)
	{
		if (pBoard->pieces[i] != Piece_E)
			count++;
	}
	return count;
}
enum BoardPiece Board_CheckRow(struct Board* pBoard, int index)
{
	if (pBoard->pieces[0 + (index * BOARD_ROW_SIZE)] == pBoard->pieces[1 + (index * BOARD_ROW_SIZE)]
		&& pBoard->pieces[0 + (index * BOARD_ROW_SIZE)] == pBoard->pieces[2 + (index * BOARD_ROW_SIZE)])
	{
		return pBoard->pieces[0 + (index * BOARD_ROW_SIZE)];
	}

	return Piece_E;
}
enum BoardPiece Board_CheckCol(struct Board* pBoard, int index)
{
	if (pBoard->pieces[0 + (index % BOARD_ROW_SIZE)] == pBoard->pieces[3 + (index % BOARD_ROW_SIZE)]
		&& pBoard->pieces[0 + (index % BOARD_ROW_SIZE)] == pBoard->pieces[6 + (index % BOARD_ROW_SIZE)])
	{
		return pBoard->pieces[0 + (index % BOARD_ROW_SIZE)];
	}

	return Piece_E;

}
enum BoardPiece Board_CheckDia(struct Board* pBoard, bool counterDia)
{
	if(counterDia == false)
	{

		if (pBoard->pieces[0] == pBoard->pieces[4]
			&& pBoard->pieces[0 ] == pBoard->pieces[8])
		{
			return pBoard->pieces[0];
		}
	}
	else
	{
		if (pBoard->pieces[2] == pBoard->pieces[4]
			&& pBoard->pieces[2] == pBoard->pieces[6])
		{
			return pBoard->pieces[2];
		}
	}
	return Piece_E;
	
}
bool Board_CheckBoardState(struct Board* pBoard)
{
	enum BoardPiece winner = Piece_E;

	for(int i = 0; i < BOARD_ROW_SIZE; i++)
	{
		winner = Board_CheckRow(pBoard, i);
		if(winner != Piece_E)
		{
			goto winnerFound;
		}
		winner = Board_CheckCol(pBoard, i);
		if (winner != Piece_E)
		{
			goto winnerFound;
		}
		
	}

	winner = Board_CheckDia(pBoard, false);
	if (winner != Piece_E)
	{
		goto winnerFound;

	}

	winner = Board_CheckDia(pBoard, true);
	if (winner != Piece_E)
	{
		goto winnerFound;
	}

	if (Board_HasFreeSpace(pBoard) == false)
	{
		pBoard->winner = Piece_E; //E means no winner
		pBoard->state = BoardState_Finished;
		return true;
	}

	pBoard->winner = Piece_E; // make sure there is no winner when no one has won.
	return false;
	
	winnerFound:
	{
		pBoard->winner = winner;
		pBoard->state = BoardState_Finished;
		return true;
	}
	
	
}
