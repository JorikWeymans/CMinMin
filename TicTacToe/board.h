#ifndef BOARD_H
#define BOARD_H

#define BoardPtr struct Board*
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




BoardPtr Board_Create();
void Board_Print(BoardPtr board);
void Board_SetPiece(BoardPtr board, int x, int y, BoardPiece data);

#endif