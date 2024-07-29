#include "AwesomeLibrary.h"

#include "game.h"
#include "board.h"
#include "word_manager.h"

using namespace std;

int main() {
	Game* game = new Game();
	game->load("vehicles");

	delete game;
	return 0;
}
