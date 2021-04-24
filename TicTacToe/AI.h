#ifndef AI_h
#define AI_h

struct Board;

void AI_DoMove(struct Board* board);
static int AI_MiniMax(struct Board* board, int depth, _Bool isAI);
static int AI_EvaluateBoardState(struct Board* board);

#endif
