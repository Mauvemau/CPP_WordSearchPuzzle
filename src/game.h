#pragma once

#include <iostream>

#include "board.h"
#include "word_manager.h"

class Game{
private:
    Board* board;
    WordManager* wm;
    std::string themeName;
    bool finished;

    // i didn't know how to call it, but it's sort of a bridge between word manager and board that i'm using for colors
    void colorFoundWordsOnBoard(std::vector<Word> wordsToColor, Color color);
    void update();
public:
    Game();
    ~Game();

    void load(std::string name, std::string themeName);
    void save();
};
