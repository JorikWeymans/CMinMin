#ifndef AI_h
#define AI_h

struct Board;

void Test(struct Board* board);
int MinMax(struct Board* board, int depth, _Bool isAI);
int AI_EvaluateBoardState(struct Board* board, _Bool isAI);

#endif
