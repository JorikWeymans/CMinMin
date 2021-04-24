#include <stdio.h> //printf
#include <stdlib.h> //system
#include <stdbool.h> //bool
#include <limits.h>//INT_MAX 
#include <time.h> // init random
#include "board.h"
#include "AI.h"

bool GetInput(struct Board* pBoard, int* x, int* y);
bool CheckCorrectInput(int* x, int* y);

int main()
{
	
	printf("Tic Tac Toe start\n");

	srand(time(NULL));

	
	// *** 
	// * alloc resources
	// ***
	struct Board* pBoard = Board_Create();
	struct AI* pAI = AI_Create(Piece_O, AIType_Random);
	enum BoardPiece playerPiece = Piece_X;



	// *** 
	// * Game Loop
	// ***
	Board_Print(pBoard);
	while (pBoard->state == BoardState_Playing)
	{

		int x, y;
		if (GetInput(pBoard, &x, &y) == false)
		{
			pBoard->state = BoardState_Finished;
			break;
		}
		system("cls");
		
		if (Board_SetPiece(pBoard, x, y, playerPiece) == false)
		{
			Board_Print(pBoard);
			printf_s("Could not place piece\n");
		}
		else if(Board_CheckBoardState(pBoard) != true)
		{
			// AI
			Board_Print(pBoard);
			printf_s("AI move\n");
			AI_MakeAMove(pAI, pBoard);
			Board_Print(pBoard);
		}
			

		if (Board_CheckBoardState(pBoard) == true)
		{
			Board_Print(pBoard);
			printf_s("There is a winner: %s\n", BoardPiece_ToString(pBoard->winner));
		}
		
	}
	
	printf_s("Game over\n");

	//***
	//* Releasing resources
	//***
	free(pBoard);
	free(pAI);
	
	system("Pause");
	
	return 0;
}

bool GetInput(struct Board* pBoard, int* x, int* y)
{
	// *** 
	// * Input
	// ***

	printf("Enter coordinates, divided by space\nAn X will be placed there\ntype -1 to quit: ");
	if (CheckCorrectInput(x, y) == false) return false;


	while ((*x < 0 || *x > 2 || *y < 0 || *y > 2) && pBoard->state == BoardState_Playing)
	{

		printf("x and y need to be between 0 and 2, divided by space: ");
		
		if (CheckCorrectInput(x, y) == false) return false;
	}

	return true;
}
bool CheckCorrectInput(int* x, int* y)
{
	
	*x = INT_MAX;// "Resetting" the input;
	*y = INT_MAX;// "Resetting" the input;
	
	char str[30];
	gets_s(str, 30);
	sscanf_s(str, "%i %i", x, y);
	//printf_s("%i %i", *x, *y);
	

	if (*x == -1 /*&& *y < 0*/)
	{
		return false;
	}
	
	return true;
}