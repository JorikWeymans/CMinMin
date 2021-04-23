#include "AI.h"
#include <limits.h>
#include "board.h"
#include "utils.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

void Test(struct Board* board)
{
	IntArray arr = Board_GetEmptyIndices(board);

	//Board_SetPieceWithIndex(board, arr.start[0], Piece_O);
	int value = MinMax(board, 0, true);;

	
	//for(int i = 0; i < arr.count; i++)
	//{
	//	Board_SetPieceWithIndex(board, arr.start[i], Piece_O);
	//	Board_Print(board);
	//	int value = MinMax(board, 3, true);
	//	printf_s("value previous board: %i", value);
	//}
	
}
int MinMax(struct Board* board, int depth, _Bool isAI)
{
	int score = AI_EvaluateBoardState(board, isAI);
	
	if (score == -100 || score == 100)
		return score;
	
	if  (Board_HasFreeSpace(board) == false)
	{
		return 0;
	}

	
	
	//IntArray arr = Board_GetEmptyIndices(board);
	if(isAI)
	{
		int maxEva = INT_MIN;
		
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			if(Board_SetPieceWithIndex(board, i, Piece_O) == true)
			{
				printf_s("Depth MAX: %i\n", depth);

				Board_Print(board);

				maxEva = max(maxEva, MinMax(board, depth + 1, false));

				Board_SetPieceWithIndex(board, i, Piece_E); //Resetting piece
			}
		}
		return maxEva;
	}
	else
	{
		int minEva = INT_MAX;

		for (int i = 0; i < BOARD_SIZE; i++)
		{
			if(Board_SetPieceWithIndex(board, i, Piece_X) == true)
			{
				printf_s("Depth Min: %i\n", depth);
				Board_Print(board);
				minEva = min(minEva, MinMax(board, depth + 1, true));


				Board_SetPieceWithIndex(board, i, Piece_E); //Resetting piece
			}
		}
		return minEva;
	}
}

int AI_EvaluateBoardState(struct Board* board, _Bool isAI)
{
	Board_CheckBoardState(board);
	switch (board->winner)
	{
		case Piece_X:
		return (isAI == true) ? 100 : -100;
		case Piece_O:
		return (isAI == true) ? 100 : -100;
		default:
		return 0; }
}
