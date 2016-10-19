#include "Render.hpp"
#include "Game.hpp"

Render::Render() {
	window.create(VideoMode(WIN_X, WIN_Y, 32), "Gomoku", Style::Close);
	loadTextures();
}

Render::~Render(void) {
}

void Render::drawBoard(Board *board) {
	window.draw(this->board);
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board->getPiece(j, i) == WHITE_PIECE) {
				if (j == get<0>(board->lastMove) && i == get<1>(board->lastMove))
					whitePiece.setColor(Color(255, 200, 200));
				setPieceAndRender(P_WHITE, i * POSA + POSB, j * POSA + POSB);
				whitePiece.setColor(Color(255, 255, 255));
			} else if (board->getPiece(j, i) == BLACK_PIECE) {
				if (j == get<0>(board->lastMove) && i == get<1>(board->lastMove))
					blackPiece.setColor(Color(255, 200, 200));
				setPieceAndRender(P_BLACK, i * POSA + POSB, j * POSA + POSB);
				blackPiece.setColor(Color(255, 255, 255));
			}
		}
	}
}

void Render::setTextAndRender(string s, int posX, int posY, int size, Color color) {
	Text text(s, font, size);
	text.setStyle(Text::Bold);
	text.setPosition(posX, posY);
	text.setColor(color);
	window.draw(text);
}

void Render::setPieceAndRender(t_player_color player, int posX, int posY) {
	if (player == P_BLACK) {
		blackPiece.setPosition(posX, posY);
		window.draw(blackPiece);
	} else {
		whitePiece.setPosition(posX, posY);
		window.draw(whitePiece);
	}
}

void Render::displayFinish(Game *game) {
	if (game->currentPlayer == P_WHITE)
		setTextAndRender("BLACK WINS", 250, 490, 100, Color::White);
	else if (game->currentPlayer == P_BLACK)
		setTextAndRender("WHITE WINS", 250, 490, 100, Color::White);
}

void Render::renderColorChoice(void) {
	setTextAndRender("CHOOSE COLOR", 150, 430, 100, Color::White);
	blackBtn.setPosition(300, 700);
	window.draw(blackBtn);
	whiteBtn.setPosition(610, 660);
	window.draw(whiteBtn);
}

void Render::drawPanel(Game *game) {
	RectangleShape rectangle(Vector2f(WIN_X, 100));

	rectangle.setOutlineColor(Color(205, 133, 63));
	rectangle.setOutlineThickness(10);
	rectangle.setFillColor(Color(245,222,179));
	rectangle.setPosition(0, WIN_Y - 100);
	window.draw(rectangle);

	setTextAndRender("Turn: ", 30, WIN_Y - 80, 40, Color::Black);
	setPieceAndRender(game->currentPlayer, 145, WIN_Y - 80);
	setTextAndRender("Captures: ", 250, WIN_Y - 80, 40, Color::Black);
	setPieceAndRender(P_BLACK, 450, WIN_Y - 80);
	setTextAndRender(to_string(game->board->nbCaptures[P_BLACK]), 520, WIN_Y - 80, 40, Color::Black);
	setPieceAndRender(P_WHITE, 560, WIN_Y - 80);
	setTextAndRender(to_string(game->board->nbCaptures[P_WHITE]), 630, WIN_Y - 80, 40, Color::Black);

	replay.setPosition(700, WIN_Y - 80);
	window.draw(replay);
}

int Render::loadTextures() {
	whitePieceTexture.setSmooth(true);
	blackPieceTexture.setSmooth(true);
	if (!boardTexture.loadFromFile("./img/board.png")) {
		cerr << "Error while loading board image" << endl;
		return EXIT_FAILURE;
	} else {
		board.setTexture(boardTexture);
		board.setScale(0.7f, 0.7f);
	}
	if (!whitePieceTexture.loadFromFile("./img/white.png")) {
		cerr << "Error while loading white piece image" << endl;
		return EXIT_FAILURE;
	} else {
		whitePiece.setTexture(whitePieceTexture);
		whitePiece.setScale(0.9f, 0.9f);
	}
	if (!blackPieceTexture.loadFromFile("./img/black.png")) {
		cerr << "Error while loading black piece image" << endl;
		return EXIT_FAILURE;
	} else {
		blackPiece.setTexture(blackPieceTexture);
		blackPiece.setScale(0.9f, 0.9f);
	}
	if (!replayTexture.loadFromFile("./img/replay.png")) {
		cerr << "Error while loading replay image" << endl;
		return EXIT_FAILURE;
	} else {
		replay.setTexture(replayTexture);
		replay.setScale(0.3f, 0.3f);
	}
	if (!blackBtnTexture.loadFromFile("./img/black-button.png")) {
		cerr << "Error while loading black button" << endl;
		return EXIT_FAILURE;
	} else {
		blackBtn.setTexture(blackBtnTexture);
		blackBtn.setScale(0.6f, 0.6f);
	}
	if (!whiteBtnTexture.loadFromFile("./img/white-button.png")) {
		cerr << "Error while loading white button" << endl;
		return EXIT_FAILURE;
	} else {
		whiteBtn.setTexture(whiteBtnTexture);
		whiteBtn.setScale(0.6f, 0.6f);
	}
	if (!font.loadFromFile("./img/arial.ttf")) {
		cerr << "Error loading font" << endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
