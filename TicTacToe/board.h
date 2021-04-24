#ifndef BOARD_H
#define BOARD_H


#define BOARD_SIZE 9
#define BOARD_ROW_SIZE 3
#include "utils.h"

struct IntArray;

enum BoardPiece
{
	Piece_E, //empty
	Piece_X,
	Piece_O 
} ;

enum BoardState
{
	BoardState_Playing,
	BoardState_Finished
};

struct Board
{
	enum BoardPiece pieces[BOARD_SIZE];
	enum BoardState state;
	enum BoardPiece winner; //no need to make another enum for this, change when OG enum becomes struct;
 };

const char* BoardPiece_ToString(enum BoardPiece data);
struct Board* Board_Create();
struct Board* Board_Copy(struct Board const * original);
void Board_Print(struct Board* pBoard);
void Board_Reset(struct Board* pBoard);

int   Board_CoordinatesToIndex(int x, int y);
_Bool Board_SpaceIsFree(struct Board* pBoard, int x, int y);
_Bool Board_HasFreeSpace(struct Board* pBoard);
_Bool Board_SetPiece(struct Board* pBoard, int x, int y, enum BoardPiece data); //returns false when piece cannot be placed
_Bool Board_SetPieceWithIndex(struct Board* pBoard, int index, enum BoardPiece data); 
void  Board_ClearPieceWithIndex(struct Board* pBoard, int index);

IntArray Board_GetEmptyIndices(struct Board* pBoard);
int Board_GetNumberOfUsedSpots(struct Board* pBoard);
enum BoardPiece Board_CheckRow(struct Board* pBoard, int index);
enum BoardPiece Board_CheckCol(struct Board* pBoard, int index);
enum BoardPiece Board_CheckDia(struct Board* pBoard, _Bool counterDia);
_Bool Board_CheckBoardState(struct Board* pBoard); //returns true if winner found

#endif