#include "Solver.hpp"

Solver::Solver() {
}

Solver::~Solver(void) {
}

template<typename U>
void Solver::listAllMoves(Board const &b, priority_queue<Board, vector<Board>, U > &queue) {
	short x, y;
	Point xy;

	unordered_map<Point, bool, simple_hash> alreadyUsed;

	for (unordered_map<Point, t_piece, simple_hash>::const_iterator it = ((Board &)b).pieces.begin(); it != ((Board &)b).pieces.end(); ++it) {
		x = get<0>(it->first), y =  get<1>(it->first);
		for (short yy = y - PADDING; yy <= y + PADDING; yy++) {
			for (short xx = x - PADDING; xx <= x + PADDING; xx++) {
				if (yy >= 0 && yy < BOARD_SIZE && xx >= 0 && xx < BOARD_SIZE && !alreadyUsed[make_pair(xx, yy)] && ((Board &)b).getPiece(xx, yy) == EMPTY_PIECE) {
					Board board = b;
					board.placePiece(xx, yy, b.turn);
					queue.push(board);
					alreadyUsed[make_pair(xx, yy)] = true;
				}
			}
		}
	}
}

Point Solver::getRandomMove(Board const &board) {
	Point res;

	while (true) {
		res = make_pair(rand() % 19, rand() % 19);
		if (((Board &)board).getPiece(get<0>(res), get<1>(res)) == EMPTY_PIECE)
			break ;
	}
	return res;
}

Point Solver::solve(Board const &board) {
	Board move;
	Point res;

	if (board.pieces.size() == 0) {
		return make_pair(BOARD_SIZE / 2, BOARD_SIZE / 2);
	}
	move = AlphaBetaMaxMove(board, MAX_DEPTH, -MAX_VALUE, MAX_VALUE);
	res = move.lastMove;
	if (((Board &)board).getPiece(get<0>(res), get<1>(res)) != EMPTY_PIECE) {
		res = getRandomMove(board);
	}
	return res;
}

bool Solver::isGameFinished(Board &board) {
	return board.threat.whiteThreats["FIVE"] != 0 || board.threat.blackThreats["FIVE"] != 0;
}

Board Solver::AlphaBetaMaxMove(Board const &board, short depth, int alpha, int beta) {
	priority_queue<Board, vector<Board>, greater<Board> > moves;
	Board current, bestMove, move;

	if (depth == 0) {
		return board;;
	}
	listAllMoves(board, moves);
	while (!moves.empty()) {
		current = moves.top();
		moves.pop();
		if (isGameFinished(current)) {
			return current;
		}
		move = AlphaBetaMinMove(current, depth - 1, alpha, beta);
		if (move.score > alpha) {
			alpha = move.score;
			bestMove = current;
			if (beta <= alpha) {
				return bestMove;
			}
		}
	}
	return bestMove;
}

Board Solver::AlphaBetaMinMove(Board const &board, short depth, int alpha, int beta) {
	priority_queue<Board, vector<Board>, less<Board> > moves;
	Board current, bestMove, move;

	if (depth == 0) {
		return board;
	}
	listAllMoves(board, moves);
	while (!moves.empty()) {
		current = moves.top();
		moves.pop();
		if (isGameFinished(current)) {
			return current;
		}
		move = AlphaBetaMaxMove(current, depth - 1, alpha, beta);
		if (move.score < beta) {
			beta = move.score;
			bestMove = current;
			if (beta <= alpha) {
				return bestMove;
			}
		}
	}
	return bestMove;
}
