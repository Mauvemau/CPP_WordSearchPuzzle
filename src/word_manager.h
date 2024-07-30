#pragma once

#include "utils.h"

#include <iostream>
#include <vector>

struct Word {
    std::string word;
    std::vector<Vector2> coords;
};

enum class WordStatus { // The value that is returned after validating the word provided by the user
    INCORRECT,
    CORRECT,
    ALREADY_FOUND
};

class WordManager {
private:
    std::vector<Word> wordsToFind;
    std::vector<Word> wordsFound;

    void pushWord(std::string word, Vector2 startCoord, Vector2 endCoord);
    std::vector<Vector2> getPositionsBetween(Vector2 start, Vector2 end);
    WordStatus validateWord(std::string word);
    void setToFound(std::string word);
public:
    WordManager();
    WordManager(std::string path);
    ~WordManager();

    void loadWords(std::string path);

    int getWordsToFindCount();
    int getWordsFoundCount();
    std::vector<Word> getWordsFound();

    bool handleWord(std::string word);

    void printFoundWords();

    void clear();
};
