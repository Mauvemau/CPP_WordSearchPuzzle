#include "board.h"
#include <fstream>

using namespace std;

void Board::loadBoard(string path) {
	static const int bufferSize = 50;
	ifstream inputStream;

	try {
		inputStream.open(path);
		if (!inputStream) {
			throw ifstream::failure("File \"" + path + "\" not found ");
		}

		char line[bufferSize];

		while (inputStream) {
			if (inputStream.fail()) {
				throw ifstream::failure("An error ocurred while reading the file! ");
			}
			inputStream.getline(line, bufferSize);

			cout << line << "\n";

		}
		cout << "File loaded successfully!\n";
		inputStream.close();
	}
	catch (ifstream::failure& exception) {
		cout << "An exception ocurred due to: " << exception.what() << "\n\n";

		if (inputStream.is_open())
			inputStream.close();
	}
}

Board::Board(string path) {
	//loadBoard(path);
	width = 10;
	height = 10;

	grid = new char* [height];

	char** aux = grid;
	for (int i = 0; i < height; i++) {
		*aux = new char[width];
		aux++;
	}
	aux = grid;
	for (int i = 0; i < height; i++) {
		char* auxX = *aux;
		for (int j = 0; j < width; j++) {
			*auxX = 'N';
			auxX++;
		}
		aux++;
	}
	aux = grid;
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
			cout << *auxX;
			auxX++;
		}
		cout << "\n";
		aux++;
	}
	aux = grid;
}