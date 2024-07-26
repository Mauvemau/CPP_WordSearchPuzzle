#pragma once

#include <iostream>

struct Vector2 {
    int x, y;
};

class Utils {
public:
    static int getRandomInt(int min, int max);
    static char getRandomLetter(bool upperCase);
};
