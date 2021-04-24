#ifndef AI_h
#define AI_h

struct Board;
enum BoardPiece;

enum AIType
{
	AIType_Random,
	AIType_MiniMax,
};
struct AI
{
	enum BoardPiece usingPiece;
	enum BoardPiece opponentsPiece;
	enum AIType type;
};

struct AI* AI_Create(enum BoardPiece pieceToUse, enum AIType type);
void AI_SetPieceToUse(struct AI* pAI, enum BoardPiece pieceToUse);

_Bool AI_MakeAMove(struct AI* pAI, struct Board* pBoard);
static _Bool AI_MakeAMove_Random(struct AI* pAI, struct Board* pBoard);
static _Bool AI_MakeAMove_MiniMax(struct AI* pAI, struct Board* board);

static int AI_MiniMax(struct AI* pAI, struct Board* board, int depth, _Bool isAI);
static int AI_EvaluateBoardState(struct AI* pAI, struct Board* pBoard);




#endif
