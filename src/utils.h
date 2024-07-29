#pragma once

#include <iostream>

static const std::string MAGIC_STRING = "ExtremelySecretAndMagicStringToExitTheGameThatTotallyNoOneWouldInputManuallyLmao";

struct Vector2 {
    int x, y;
};

class Utils {
public:
    static std::string customCharacterInput();
    static std::string upCase(std::string str);
    static std::string lowCase(std::string str);
    static int getRandomInt(int min, int max);
    static char getRandomLetter(bool upperCase);
};
