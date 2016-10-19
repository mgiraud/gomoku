#ifndef BOARD_HPP
# define BOARD_HPP

# define BOARD_SIZE 19

# define INV(X) ((X) == (BLACK_PIECE) ? (WHITE_PIECE) : (BLACK_PIECE))
# define PLAYER(X) ((X) == (BLACK_PIECE) ? (P_BLACK) : (P_WHITE))

# include "Player.hpp"
# include "AThreat.hpp"
# include <vector>
# include <unordered_map>
using namespace std;

typedef std::pair<short, short> Point;

struct simple_hash {
	size_t operator()(const Point& p) const {
		return p.first ^ p.second;
	}
};

typedef enum 	e_piece {
	BLACK_PIECE = 'x',
	WHITE_PIECE = 'o',
	EMPTY_PIECE = '.',
	OUT_OF_BOARD = '\0'
}				t_piece;

class Board {
public:
	AThreat 					threat;
	bool						lastMoveIsCapture;
	int							nbCaptures[2];
	int							score;
	Point						lastMove;
	t_piece						turn;
	unordered_map<Point, t_piece, simple_hash>	pieces;

	static string orientation[8];
	static unordered_map<string, Point> orientationInc;

	Board(void);
	Board(Board const &rhs);
	virtual ~Board(void);

	void clear(void);
	void print(void);
	bool placePiece(short x, short y, t_piece piece);
	t_piece getPiece(short x, short y);
	bool hasXPiecesInRow(short x, short y, int nb, bool (*f)(int, int));
	int countConnectedPieces(short x, short y, t_piece piece, string ori);
	bool rowEndsWithPiece(short x, short y, t_piece initial, t_piece piece, string ori);
	void removeCaptures(void);
	void removePiece(short x, short y);
};

bool operator>(Board const &a, Board const &b);
bool operator<(Board const &a, Board const &b);
bool operator>=(Board const &a, Board const &b);
bool operator<=(Board const &a, Board const &b);
bool operator==(Board const &a, Board const &b);
bool operator!=(Board const &a, Board const &b);

#endif
