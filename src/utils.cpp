#include "utils.h"

int Utils::getRandomInt(int min, int max) {
    if (min > max) {
        int aux = max;
        max = min;
        min = aux;
    }

    return (rand() % (abs(max - min) + 1) + min);
}

char Utils::getRandomLetter(bool upperCase){
    int lowerBound = upperCase ? 65 : 97;
    int upperBound = upperCase ? 90 : 122;
    return static_cast<char>(getRandomInt(lowerBound, upperBound));
}
