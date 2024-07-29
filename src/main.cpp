#include "AwesomeLibrary.h"

#include "game.h"
#include "board.h"
#include "word_manager.h"

using namespace std;

int main() {
	Game* game = new Game();
	//game->load("computers");
	game->load("cars");
	//game->load("animals");

	delete game;
	return 0;
}
