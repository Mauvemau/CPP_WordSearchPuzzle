#include "board.h"

#include <fstream>
#include <string>

#include "utils.h"

using namespace std;

Board::Board(string path) {
	width = 0;
	height = 0;

	grid = new char* [maxBoardHeight];
	char** aux = grid;
	for (int i = 0; i < maxBoardHeight; i++) {
		*aux = new char[maxBoardWidth];
		aux++;
	}
	aux = grid;

	loadBoard(path);
	cout << "Board created!\n";
}

Board::~Board() {
	char** aux = grid;
	for (int i = 0; i < height; i++) {
		delete[] * aux;
		aux++;
	}
	delete[] grid;
	cout << "Board deleted.\n";
}

// Private

void Board::pushLine(std::string line) {
	char** aux = grid;
	for(int i = 0; i < height; i++) {
		aux++;
	}
	const char* strPtr = line.c_str();
	char* auxX = *aux;
	for (int i = 0; static_cast<size_t>(i) < line.size(); i++) {
		if(*strPtr == '*'){
			*auxX = Utils::getRandomLetter(true);
		}else {
			*auxX = *strPtr;
		}
		strPtr++;
		auxX++;
	}
	height++;
}

void Board::loadBoard(string path) {
	ifstream inputStream;

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
		cout << "File loaded successfully!\n";
		inputStream.close();
	}
	catch (ifstream::failure& exception) {
		cout << "An exception ocurred due to: " << exception.what() << "\n\n";

		if (inputStream.is_open())
			inputStream.close();
	}

	cout << "Width: " << width << "\n";
	cout << "Height: " << height << "\n";
}

// Public

void Board::print() {
	char** aux = grid;
	for (int i = 0; i < height; i++) {
		char* auxX = *aux;
		for (int j = 0; j < width; j++) {
			if(*auxX){
				cout << *auxX << " ";
			}else {
				cout << "  "; // If the puzzle is asymmetrical we just draw an empty space
			}
			auxX++;
		}
		cout << "\n";
		aux++;
	}
	aux = grid;
}
