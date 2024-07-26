#include "AwesomeLibrary.h"
#include "board.h"

using namespace std;

int main() {
	Board* board = new Board("soup.txt");
	board->print();

	delete board;

#ifdef _WIN32
	getKey();
#endif
	return 0;
}
