#ifndef BOARD_H
#define BOARD_H

#define pBoard struct Board*
#define BOARD_SIZE 9
#define BOARD_ROW_SIZE 3

typedef enum 
{
	Piece_E, //empty
	Piece_X,
	Piece_O,
} BoardPiece;


typedef enum
{
	Sate_Playing,
	Sate_Finished
} BoardState;

struct Board
{
	BoardPiece pieces[BOARD_SIZE];
	BoardState state;



	
};




pBoard Board_Create();
void Board_Print(pBoard board);
void Board_SetPiece(pBoard board, int x, int y, BoardPiece data);

#endif