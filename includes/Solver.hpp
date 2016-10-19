#ifndef SOLVER_HPP
# define SOLVER_HPP

#include "Board.hpp"
#include <queue>

#define PADDING 1
#define MAX_DEPTH 2

class Solver {

public:
	Solver(void);
	~Solver(void);

	bool isGameFinished(Board &board);
	Board minMaxAlphaBeta(Board const &board, int depth, int alpha, int beta);
	Point solve(Board const &board);
	Point getRandomMove(Board const &board);
	template<typename U>
	void listAllMoves(Board const &b, priority_queue<Board, vector<Board>, U > &queue);
	Board AlphaBetaMaxMove(Board const &board, short depth, int alpha, int beta);
	Board AlphaBetaMinMove(Board const &board, short depth, int alpha, int beta);
};

#endif
