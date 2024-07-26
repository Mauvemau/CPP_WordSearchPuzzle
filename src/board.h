#pragma once

#include <iostream>

class Board {
private:
	const int maxBoardWidth = 30;
	const int maxBoardHeight = 30;
	char** grid;
	int width;
	int height;

	void pushLine(std::string line);
	void loadBoard(std::string path);
public:
	Board(std::string path);
	~Board();

	void print();
};
