#include "AI.h"
#include <limits.h>
#include "board.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>


struct AI* AI_Create(enum BoardPiece pieceToUse, enum AIType type)
{
	struct AI* pAI = (struct AI*)malloc(sizeof(struct AI));
	if (pAI == NULL) return NULL;

	pAI->usingPiece = pieceToUse;
	pAI->opponentsPiece = (pieceToUse == Piece_O) ? Piece_X : Piece_O;

	pAI->type = type;
	
	return pAI;
	
}
bool AI_MakeAMove(struct AI* pAI, struct Board* pBoard)
{
	switch (pAI->type)
	{
	case AIType_Random:
		return AI_MakeAMove_Random(pAI, pBoard);
	case AIType_MiniMax:
		return AI_MakeAMove_MiniMax(pAI, pBoard);
	default:
		return false;
	}
}

static bool AI_MakeAMove_Random(struct AI* pAI, struct Board* pBoard)
{

	IntArray arr = Board_GetEmptyIndices(pBoard);

	if (arr.count < 0) return false;
	
	Board_SetPieceWithIndex(pBoard, arr.start[rand() % arr.count], pAI->usingPiece);
	
	free(arr.start);

	return true;
}
static bool AI_MakeAMove_MiniMax(struct AI* pAI, struct Board* board)
{
	int bestVal = INT_MIN;
	int bestMove = -1;
	//coping the board once so that we don't change any unwanted board settings like board::state
	struct Board* pTestingBoard = Board_Copy(board);

	// *** Edge cases
	// empty board => bestMove == middle, no need to calculate (minmax takes the middle by default but calculation is high)
	int usedSpots = Board_GetNumberOfUsedSpots(board);
	if (usedSpots == 0)
	{
		bestMove = 4;
		goto moveDetermined;
	}
	// only 1
	if (usedSpots == 1)
	{
		//not in the middle => bestMove == middle(minmax takes 0, 0 by default if not corner piece but the middle piece is better
		if (board->pieces[4] == Piece_E)
		{
			bestMove = 4;
			goto moveDetermined;
		}
		// else in the middle => take 0,0 (minmax takes this by default but no need to calculate)
		bestMove = 0;
		goto moveDetermined;

	}


	// *** Minmax
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if (pTestingBoard->pieces[i] == Piece_E)
		{
			pTestingBoard->pieces[i] = pAI->usingPiece;

			int  thisVal = AI_MiniMax(pAI, pTestingBoard, 0, false);

			pTestingBoard->pieces[i] = Piece_E;

			if (thisVal > bestVal)
			{
				bestMove = i;
				bestVal = thisVal;
			}
		}
	}

	free(pTestingBoard);


moveDetermined:
	{
		if (bestMove != -1)
		{
			Board_SetPieceWithIndex(board, bestMove, pAI->usingPiece);
			return true;
		}
		return false;
	}


}

static int AI_MiniMax(struct AI* pAI, struct Board* board, int depth, _Bool isAI)
{
	int score = AI_EvaluateBoardState(pAI, board);
	
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
			if(Board_SetPieceWithIndex(board, i, pAI->usingPiece))
			{
				maxEva = max(maxEva, AI_MiniMax(pAI, board, depth + 1, false));
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
			if (Board_SetPieceWithIndex(board, i, pAI->opponentsPiece))
			{
				minEva = min(minEva, AI_MiniMax(pAI, board, depth + 1, true));
				Board_ClearPieceWithIndex(board, i);
			}
		}
		return minEva;
	}
}

static int AI_EvaluateBoardState(struct AI* pAI, struct Board* pBoard)
{
	Board_CheckBoardState(pBoard);
	switch (pBoard->winner)
	{
		case Piece_X:
		case Piece_O:
			return pAI->usingPiece == pBoard->winner ? 100 : -100;
		default:
			return 0;
	}
}
