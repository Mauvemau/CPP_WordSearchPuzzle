#include "board.h"

#include <fstream>
#include <string>

using namespace std;

Board::Board() {
	width = 0;
	height = 0;

	grid = new Slot * [maxBoardHeight];
	Slot** aux = grid;
	for (int i = 0; i < maxBoardHeight; i++) {
		*aux = new Slot[maxBoardWidth];
		aux++;
	}
	aux = grid;

	cout << "Board created!\n";
}

Board::Board(string path) {
	width = 0;
	height = 0;

	grid = new Slot* [maxBoardHeight];
	Slot** aux = grid;
	for (int i = 0; i < maxBoardHeight; i++) {
		*aux = new Slot[maxBoardWidth];
		aux++;
	}
	aux = grid;

	load(path);
	cout << "Board created!\n";
}

Board::~Board() {
	Slot** aux = grid;
	for (int i = 0; i < maxBoardHeight; i++) {
		delete[] *aux;
		aux++;
	}
	delete[] grid;
	cout << "Board destroyed.\n";
}

// Private

void Board::pushLine(string line) {
	Slot** aux = grid;
	aux += height;

	const char* strPtr = line.c_str();
	Slot* auxX = *aux;
	for (int i = 0; static_cast<size_t>(i) < line.size(); i++) {
		if(*strPtr == '*'){
			auxX->ch = Utils::getRandomLetter(true);
		}else {
			auxX->ch = *strPtr;
		}
		auxX->col = Color::BWHITE;
		strPtr++;
		auxX++;
	}
	height++;
}

// Public

void Board::colorSlot(Vector2 coord, Color color) {
	if (coord.y < height && coord.y > -1 && coord.x < width && coord.y > -1) {
		Slot** aux = grid;
		aux += coord.y;
		Slot* auxX = *aux;
		auxX += coord.x;

		auxX->col = color;
	}
	else {
		cout << "ERROR: color cursor out of bouds!!\n";
	}
}

void Board::colorSlots(vector<Vector2> coordsToColor, Color color) {
	for (vector<Vector2>::iterator it = coordsToColor.begin(); it != coordsToColor.end(); ++it) {
		colorSlot(*it, color);
	}
}

void Board::load(string path) {
	ifstream inputStream;
	width = 0;
	height = 0;

	try {
		inputStream.open(path);
		if (!inputStream) {
			throw ifstream::failure("File \"" + path + "\" not found ");
		}

		string line;

		while (getline(inputStream, line)) {
			if (inputStream.fail()) {
				throw ifstream::failure("An error occurred while reading the file! ");
			}
			if (static_cast<size_t>(width) < line.size()) {
				width = line.size();
			}

			pushLine(line);
		}
		cout << "Board loaded successfully with " << width << "x" << height << " lines!!\n";
		inputStream.close();
	}
	catch (ifstream::failure& exception) {
		cout << "An exception ocurred due to: " << exception.what() << "\n\n";

		if (inputStream.is_open())
			inputStream.close();
	}
}

void Board::print() {
	Slot** aux = grid;

	for (int i = 0; i < width; i++) {
		cout << "+---";
	}
	cout << "+\n";

	for (int i = 0; i < height; i++) {
		Slot* auxX = *aux;

		for (int j = 0; j < width; j++) {
			cout << "| ";
			setForegroundColor(auxX->col);
			if (auxX->ch) {
				cout << auxX->ch;
			}
			else {
				cout << " "; // If the puzzle is asymmetrical we just draw an empty space
			}
			setForegroundColor(Color::BWHITE);
			cout << " ";
			auxX++;
		}
		cout << "|\n";

		for (int j = 0; j < width; j++) {
			cout << "+---";
		}
		cout << "+\n";

		aux++;
	}
	setForegroundColor(Color::WHITE);
	aux = grid;
}
