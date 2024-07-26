#include "board.h"
#include <fstream>

#include "utils.h"

using namespace std;

void Board::pushLine(std::string line){

	char** aux = grid;
	for(int i = 0; i < height; i++){
		aux++;
	}
	const char *strPtr = line.c_str();
	char* auxX = *aux;
	for (int i = 0; i < line.size(); i++) {
		if(*strPtr == '*'){
			*auxX = Utils::getRandomLetter(true);
		}else{
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
			if (width < line.size()) {
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

/*
 f o*r (int i = 0; i < height; i++) {
 char* auxX = *aux;
 for (int j = 0; j < width; j++) {
	 *auxX = 'N';
	 auxX++;
	 }
	 aux++;
	 }
	 aux = grid;
	 */
