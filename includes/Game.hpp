#ifndef GAME_HPP
# define GAME_HPP

#include <iostream>
#include <string>
using namespace std;

# define PIECE(X) ((X) == (P_BLACK) ? (BLACK_PIECE) : (WHITE_PIECE))

# include "Board.hpp"
# include "Player.hpp"
# include "Solver.hpp"
# include "Render.hpp"
# include <time.h>

typedef enum 	e_step {
	STEP_COLOR,
	STEP_GAME
}				t_step;

class Board;
class Solver;
class Game {

public:
	bool			isFinished;
	Board			*board;
	Render			*render;
	Solver			*solver;
	Player			*player[2];
	Event			event;
	t_step			step;
	static t_player_color	currentPlayer;

	Game(void);
	~Game(void);
	bool 			loop(void);
	bool			getAIMove(void);
	void 			setNext(void);
	void 			renderGame(void);
	bool 			playOneTurn(Event *event);
	bool 			getPlayerMove(Event *event);
	bool			clickedReplay(Event *event);
	void 			setColorChoice(void);
	bool 			hasClickedOnSprite(Sprite sprite);
};

#endif
