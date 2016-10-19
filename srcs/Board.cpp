#include "Board.hpp"

string Board::orientation[] = {"NW", "SE", "N", "S", "W", "E", "SW", "NE"};
unordered_map<string, Point >Board::orientationInc = {
	{"NW",make_pair(-1, -1)},
	{"N",make_pair(0, -1)},
	{"NE",make_pair(1, -1)},
	{"E",make_pair(1, 0)},
	{"SE",make_pair(1, 1)},
	{"S",make_pair(0, 1)},
	{"SW",make_pair(-1, 1)},
	{"W",make_pair(-1, 0)}
};

Board::Board(void) {
	lastMove = make_pair(-1, -1);
	score = 0;
	nbCaptures[P_BLACK] = 0;
	nbCaptures[P_WHITE] = 0;
	turn = BLACK_PIECE;
	lastMoveIsCapture = false;
}

Board::~Board(void) {
}

Board::Board(Board const &rhs) {
	lastMove = rhs.lastMove;
	turn = rhs.turn;
	memcpy(nbCaptures, rhs.nbCaptures, sizeof(int[2]));
	lastMoveIsCapture = rhs.lastMoveIsCapture;
	for (unordered_map<Point, t_piece, simple_hash>::const_iterator it = rhs.pieces.begin(); it != rhs.pieces.end(); ++it) {
		pieces[(*it).first] = (*it).second;
	}
	score = rhs.score;
}

void Board::removeCaptures(void) {
	Point inc;
	short x = get<0>(lastMove);
	short y = get<1>(lastMove);

	lastMoveIsCapture = false;
	for (short i = 0; i < 8; i++) {
		inc = orientationInc[orientation[i]];
		if (countConnectedPieces(x + get<0>(inc), y + get<1>(inc), INV(turn), orientation[i]) == 2 &&
			rowEndsWithPiece(x + get<0>(inc), y + get<1>(inc), INV(turn), turn, orientation[i])) {
			removePiece(x + get<0>(inc), y + get<1>(inc));
			removePiece(x + get<0>(inc) * 2, y + get<1>(inc) * 2);
			lastMoveIsCapture = true;
			nbCaptures[PLAYER(turn)] += 1;
		}
	}
}

int	 Board::countConnectedPieces(short x, short y, t_piece piece, string ori) {
	Point inc = orientationInc[ori];

	if (x < 0 || y < 0 || x >= BOARD_SIZE || y >= BOARD_SIZE || getPiece(x, y) != piece) {
		return (0);
	}
	return (1 + countConnectedPieces(x + get<0>(inc), y + get<1>(inc), piece, ori));
}

bool Board::rowEndsWithPiece(short x, short y, t_piece initial, t_piece piece, string ori) {
	Point inc = orientationInc[ori];

	if (getPiece(x, y) == piece) {
		return true;
	} else if (x < 0 || y < 0 || x >= BOARD_SIZE || y >= BOARD_SIZE || getPiece(x, y) != initial) {
		return false;
	}
	return (rowEndsWithPiece(x + get<0>(inc), y + get<1>(inc), initial, piece, ori));
}

bool Board::hasXPiecesInRow(short x, short y, int nb, bool (*f)(int, int)) {
	short i = 0;
	t_piece piece = getPiece(x, y);

	while (i < 8) {
		if ((*f)(countConnectedPieces(x, y, piece, orientation[i]) +
			countConnectedPieces(x, y, piece, orientation[i + 1]) - 1, nb)) {
			return true;
		}
		i += 2;
	}
	return false;
}

bool Board::placePiece(short x, short y, t_piece piece) {
	Point xy;

	xy = make_pair(x, y);
	if (x < BOARD_SIZE && y < BOARD_SIZE && getPiece(x, y) == EMPTY_PIECE) {
		pieces[xy] = piece;
		if (threat.isBrokenThree(*this, x, y) && threat.isXStraight(*this, x, y, 3)) {
			pieces.erase(xy);
			return false;
		}
		lastMove = make_pair(x, y);
		removeCaptures();
		threat.computeThreats(*this);
		turn = INV(turn);
		return true;
	}
	return false;
}

void Board::removePiece(short x, short y) {
	unordered_map<Point, t_piece, simple_hash>::iterator it;

	it = pieces.find(make_pair(x, y));
	pieces.erase(it);
}

t_piece Board::getPiece(short x, short y) {
	pair<int, int> xy;

	xy = make_pair(x, y);
	if (x < 0 ||  y < 0 || x >= BOARD_SIZE || y >= BOARD_SIZE)
		return OUT_OF_BOARD;
	if (pieces.find(xy) == pieces.end()) {
		return EMPTY_PIECE;
	}
	return pieces[xy];
}

bool operator>(Board const &a, Board const &b) {
	return (a.score > b.score);
}

bool operator<(Board const &a, Board const &b) {
	return (a.score < b.score);
}

bool operator>=(Board const &a, Board const &b) {
	return (a.score >= b.score);
}

bool operator<=(Board const &a, Board const &b) {
	return (a.score <= b.score);
}

bool operator==(Board const &a, Board const &b) {
	return (a.score == b.score);
}

bool operator!=(Board const &a, Board const &b) {
	return (a.score != b.score);
}
