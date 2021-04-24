#include <stdio.h> //printf
#include <stdlib.h> //system
#include <stdbool.h> //bool
#include <limits.h>//INT_MAX 
#include <time.h> // init random
#include "board.h"
#include "AI.h"

bool GetInput(struct Board* pBoard,enum BoardPiece playerPiece, int* x, int* y);
bool CheckCorrectInput(int* x, int* y);

char title[] = "***************************\n*** CMinMin Tic-Tac-Toe ***\n***************************\n";

int main()
{
	srand(time(NULL));

	
	// *** 
	// * alloc resources
	// ***
	struct Board* pBoard = Board_Create();
	struct AI* pAI = AI_Create(Piece_O, AIType_Random);
	enum BoardPiece playerPiece = Piece_X;

	startOfProgram:
	{
		Board_Reset(pBoard);
		int difficultySelect = -1;
		while (difficultySelect == -1)
		{
			system("cls");
			printf_s(title);
			printf_s("Welcome! Please select a difficulty for the AI:\n 1. Impossible(MiniMax)\n 2. Easy(random)\n");


			difficultySelect = Input_GetInt();
			if (difficultySelect == 1)
			{
				printf_s("Difficulty Impossible selected!\n");
				pAI->type = AIType_MiniMax;
			}
			else if (difficultySelect == 2)
			{
				printf_s("Difficulty Easy selected!\n");
				pAI->type = AIType_Random;

			}
			else
			{
				difficultySelect = -1;
			}

		}
	}


	{
		int pieceToUse = -1;
		while (pieceToUse == -1)
		{
			printf_s("Select if you want to use the X or O char:\n 1. Use X\n 2. Use O\n");
			pieceToUse = Input_GetInt();
			if (pieceToUse == 1)
			{
				printf_s("You are using X!\n");
				playerPiece = Piece_X;
				AI_SetPieceToUse(pAI, Piece_O);
			}
			else if (pieceToUse == 2)
			{
				printf_s("You are using Y!\n");
				pAI->type = AIType_Random;
				playerPiece = Piece_O;
				AI_SetPieceToUse(pAI, Piece_X);

			}
			else
			{
				pieceToUse = -1;
			}
		}
	}

	
	// *** 
	// * Game Loop
	// ***
	Board_Print(pBoard);
	while (pBoard->state == BoardState_Playing)
	{

		int x, y;
		if (GetInput(pBoard, playerPiece,  &x, &y) == false)
		{
			pBoard->state = BoardState_Finished;
			break;
		}
	
		system("cls");
		printf_s(title);
		
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
		Board_CheckBoardState(pBoard);
	}
	
	system("cls");
	printf_s(title);
	Board_Print(pBoard);

	if(pBoard->winner == Piece_O || pBoard->winner == Piece_X)
	{
		printf_s((pBoard->winner == playerPiece) ? "Congratz! You have won the game\n" : "Too bad! The AI has won\n");
		
	}
	else
	{
		printf_s("Game over! It was a draw\n");
	}

	{
		int playAgain = -1;
		while(playAgain == -1)
		{
			printf_s("Input 1 to play again, everything else will close the program\n");
			playAgain = Input_GetInt();

			if(playAgain == 1)
			{
				goto startOfProgram;
			}
			if(playAgain == -1)
			{
				playAgain = 0;
			}
		}
	}


	//***
	//* Releasing resources
	//***
	free(pBoard);
	free(pAI);

	
	return 0;
}

bool GetInput(struct Board* pBoard, enum BoardPiece playerPiece, int* x, int* y)
{
	// *** 
	// * Input
	// ***

	printf("Enter coordinates, divided by space\nAn %s will be placed there\ntype -1 to quit: ", BoardPiece_ToString(playerPiece));
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