#ifndef RENDER_HPP
# define RENDER_HPP

# define WIN_X 1120
# define WIN_Y 1220
# define POSA 58
# define POSB 9

#include <iostream>
#include "Board.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Game;
class Board;
class Render {

public:
	RenderWindow window;
	Texture 	boardTexture;
	Texture 	whitePieceTexture;
	Texture 	blackPieceTexture;
	Texture 	replayTexture;
	Texture 	blackBtnTexture;
	Texture 	whiteBtnTexture;

	Font		font;

	Sprite		board;
	Sprite		blackPiece;
	Sprite		whitePiece;
	Sprite		replay;
	Sprite		blackBtn;
	Sprite		whiteBtn;

	Render(void);
	~Render(void);
	int loadTextures();
	void mouseMove(Board *board);
	void drawBoard(Board *board);
	void drawPanel(Game *game);
	void renderColorChoice(void);
	void setPieceAndRender(t_player_color player, int posX, int posY);
	void setTextAndRender(string s, int posX, int posY, int size, Color color);
	void displayFinish(Game *game);
};

#endif
