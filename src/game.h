#pragma once

#include <iostream>

#include "board.h"
#include "word_manager.h"

class Game{
private:
    Board* board;
    WordManager* wm;

    void update();
public:
    Game();
    ~Game();

    void load(std::string name);
};
