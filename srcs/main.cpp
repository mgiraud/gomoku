#include "Game.hpp"

int main() {
	bool replay = true;
	Game *game;

	while (replay) {
		game = new Game();
		if (game->step == STEP_COLOR) {
			game->setColorChoice();
		}
		if (game->step == STEP_GAME) {
			replay = game->loop();
		}
		delete game;
	}
	return (EXIT_SUCCESS);
}
