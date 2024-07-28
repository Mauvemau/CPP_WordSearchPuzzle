#pragma once
#include "AwesomeLibrary.h"

#include <iostream>

struct Slot{
	char ch;
	Color col;
};

class Board {
private:
	const int maxBoardWidth = 30;
	const int maxBoardHeight = 30;
	Slot** grid;
	int width;
	int height;

	void pushLine(std::string line);
	void loadBoard(std::string path);
public:
	Board(std::string path);
	~Board();

	void print();
};
