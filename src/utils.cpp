#include "utils.h"
#include "AwesomeLibrary.h"

using namespace std;

string Utils::customCharacterInput() {
    string returnString = "";
    char input;
    do {
        input = getKey(true);

        switch (input) {
        case KEY_ESC:
            returnString = MAGIC_STRING;
            cout << "\n";
            break;
        case KEY_ENTER:
            cout << "\n";
            break;
        case static_cast<char>(8):
            if (returnString.size() > 0) {
                cout << "\b \b";
                returnString.pop_back();
            }
            break;
        default:
            returnString.push_back(input);
            cout << input;
            break;
        }
    } while (input != KEY_ESC && input != KEY_ENTER);
    return returnString;
}

string Utils::upCase(string str) {
    string upperString = str;
    for (size_t i = 0; i < upperString.size(); ++i) {
        upperString[i] = toupper(static_cast<char>(upperString[i]));
    }
    return upperString;
}

string Utils::lowCase(string str) {
    string lowerString = str;
    for (size_t i = 0; i < lowerString.size(); ++i) {
        lowerString[i] = tolower(static_cast<char>(lowerString[i]));
    }
    return lowerString;
}

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
