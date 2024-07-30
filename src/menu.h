#pragma once

#include <iostream>
#include <vector>

#include "game.h"
#include "utils.h"

struct GameData {
	std::string id;
	std::string displayName;
	Vector2 size;
	int amountWords;
};

class Menu {
private:
	std::vector<GameData> loadableGames;
	Game* game;
	bool exit;

	void gameSelectMenu();
	void userMenu();
	void update();
public:
	Menu();
	~Menu();

	void addGame(GameData data);
	void run();
};