#ifndef BOARD_H
#define BOARD_H

#define BoardPtr struct Board*
#define BOARD_SIZE 9
#define BOARD_ROW_SIZE 3

typedef enum 
{
	Piece_E = 0, //empty
	Piece_X = 1,
	Piece_O = 5,
} BoardPiece;


typedef enum
{
	BoardState_Playing,
	BoardState_Finished
} BoardState;


struct Board
{
	BoardPiece pieces[BOARD_SIZE];
	BoardState state;
	BoardPiece winner; //no need to make another enum for this, change when OG enum becomes struct;
};

const char* BoardPiece_ToString(BoardPiece data);
BoardPtr Board_Create();
void Board_Print(BoardPtr board);

int Board_CoordinatesToIndex(int x, int y);
_Bool SpaceIsFree(BoardPtr board, int x, int y);
_Bool Board_SetPiece(BoardPtr board, int x, int y, BoardPiece data);

BoardPiece Board_CheckRow(BoardPtr board, int index);
BoardPiece Board_CheckCol(BoardPtr board, int index);
BoardPiece Board_CheckDia(BoardPtr board, _Bool counterDia);
_Bool Board_CheckBoardState(BoardPtr board); //returns true if winner found

#endif