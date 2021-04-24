#ifndef BOARD_H
#define BOARD_H


#define BOARD_SIZE 9
#define BOARD_ROW_SIZE 3
#include "utils.h"

struct IntArray;

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
struct Board* Board_Create();
struct Board* Board_Copy(struct Board const * original);
void Board_Print(struct Board* pBoard);

int Board_CoordinatesToIndex(int x, int y);
_Bool Board_SpaceIsFree(struct Board* pBoard, int x, int y);
_Bool Board_HasFreeSpace(struct Board* pBoard);
_Bool Board_SetPiece(struct Board* pBoard, int x, int y, BoardPiece data); //returns false when piece cannot be placed
_Bool Board_SetPieceWithIndex(struct Board* pBoard, int index, BoardPiece data); 
void Board_ClearPieceWithIndex(struct Board* pBoard, int index);

IntArray Board_GetEmptyIndices(struct Board* pBoard);

BoardPiece Board_CheckRow(struct Board* pBoard, int index);
BoardPiece Board_CheckCol(struct Board* pBoard, int index);
BoardPiece Board_CheckDia(struct Board* pBoard, _Bool counterDia);
_Bool Board_CheckBoardState(struct Board* pBoard); //returns true if winner found

#endif