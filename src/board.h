#pragma once

#include <iostream>

class Board {
private:
	char** grid;
	int width;
	int height;

	void loadBoard(std::string path);
public:
	Board(std::string path);
	~Board();

	void print();
};