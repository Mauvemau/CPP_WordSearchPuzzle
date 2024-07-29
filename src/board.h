#pragma once
#include "AwesomeLibrary.h"

#include <iostream>
#include <vector>

#include "utils.h"

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
public:
	Board();
	Board(std::string path);
	~Board();

	void colorSlot(Vector2 coord, Color color);
	void colorSlots(std::vector<Vector2> coordsToColor, Color color);

	void load(std::string path);

	void print();
};
