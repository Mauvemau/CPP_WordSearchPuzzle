#pragma once

#include "utils.h"

#include <iostream>
#include <vector>

struct Word{
    std::string word;
    std::vector<Vector2> coords;
};

class WordManager {
private:
    std::vector<Word> words;

    void pushWord(std::string word, Vector2 startCoord, Vector2 endCoord);
    void loadWords(std::string path);
    std::vector<Vector2> getPositionsBetween(Vector2 start, Vector2 end);
public:
    WordManager(std::string path);
    ~WordManager();

    void print();
};
