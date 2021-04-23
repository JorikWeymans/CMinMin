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
	MinMax(board, 0, true);;

	
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

	
	
	IntArray arr = Board_GetEmptyIndices(board);
	if(isAI)
	{
		
		int maxEva = INT_MIN;
		
		for (int i = 0; i < arr.count; i++)
		{
			BoardPtr pCopied = Board_Copy(board);
			
			if(Board_SetPieceWithIndex(pCopied, arr.start[i], Piece_O) == true)
			{
				//maxEva = AI_EvaluateBoardState(copiedState, isAI);
				printf_s("Depth MAX: %i\n", depth);

				Board_Print(pCopied);

				maxEva = max(maxEva, MinMax(pCopied, depth + 1, false));

				Board_SetPieceWithIndex(pCopied, arr.start[i], Piece_E); //Resetting piece
			}

			

			

			free(pCopied);
		}
		return maxEva;
	}
	else
	{
		
		int minEva = INT_MAX;

		for (int i = 0; i < arr.count; i++)
		{
			BoardPtr copiedState = Board_Copy(board);

			if(Board_SetPieceWithIndex(copiedState, arr.start[i], Piece_X) == true)
			{
				//minEva = AI_EvaluateBoardState(copiedState, isAI);
			//printf_s("Depth Min: %i || Evaluated: %i\n", depth, minEva);
				printf_s("Depth Min: %i\n", depth);
				Board_Print(board);

				//int eva = MinMax(copiedState, depth - 1, true);

				minEva = min(minEva, MinMax(Board_Copy(copiedState), depth + 1, true));


				Board_SetPieceWithIndex(copiedState, arr.start[i], Piece_E); //Resetting piece


				free(copiedState);
			}
			
			
		}

		return minEva;
	}
	

	free(arr.start);
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
