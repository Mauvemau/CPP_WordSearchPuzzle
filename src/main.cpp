#include "AwesomeLibrary.h"
#include "board.h"
#include "word_manager.h"

using namespace std;

int main() {
	Board* board = new Board("vehicles.txt");
	WordManager* wm = new WordManager("vehicles_words.txt");

	cout << "\n";

	board->print();
	cout << "\n";
	wm->print();

	cout << "\n";

	delete board;
	delete wm;

#ifdef _WIN32
	getKey();
#endif
	return 0;
}
