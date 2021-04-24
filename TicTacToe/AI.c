#include "AI.h"
#include <limits.h>
#include "board.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

bool AI_DoMove(struct Board* board)
{
	int bestVal = INT_MIN;
	int bestMove = -1;


	//coping the board once so that we don't change any unwanted board settings like board::state
	struct Board* pTestingBoard = Board_Copy(board);
	
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if (pTestingBoard->pieces[i] == Piece_E)
		{
			pTestingBoard->pieces[i] = Piece_O;

			int  thisVal = AI_MiniMax(pTestingBoard, 0, false);

			pTestingBoard->pieces[i] = Piece_E;

			if (thisVal > bestVal)
			{
				bestMove = i;
				bestVal = thisVal;
			}
		}
	}
	
	free(pTestingBoard);

	if(bestMove != -1)
	{
		Board_SetPieceWithIndex(board, bestMove, Piece_O);
		return true;
	}
	return false;
	
}

static int AI_MiniMax(struct Board* board, int depth, _Bool isAI)
{
	int score = AI_EvaluateBoardState(board);
	
	if (score == 100 || score == -100)
		return score;
	
	if  (Board_HasFreeSpace(board) == false)
	{
		return 0;
	}
	
	if(isAI)
	{
		int maxEva = INT_MIN;
		
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			if(Board_SetPieceWithIndex(board, i, Piece_O))
			{
				maxEva = max(maxEva, AI_MiniMax(board, depth + 1, false));
				Board_ClearPieceWithIndex(board, i);
			}
		}
		return maxEva;
	}
	else
	{
		int minEva = INT_MAX;

		for (int i = 0; i < BOARD_SIZE; i++)
		{
			if (Board_SetPieceWithIndex(board, i, Piece_X))
			{
				minEva = min(minEva, AI_MiniMax(board, depth + 1, true));
				Board_ClearPieceWithIndex(board, i);
			}
		}
		return minEva;
	}
}

static int AI_EvaluateBoardState(struct Board* board)
{
	Board_CheckBoardState(board);
	switch (board->winner)
	{
		case Piece_X:
			return -100;
		case Piece_O:
			return 100;
		default:
			return 0;
	}
}
