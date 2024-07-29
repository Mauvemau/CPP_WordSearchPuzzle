#include "word_manager.h"

#include <string>
#include <fstream>
#include <cmath>

#include "AwesomeLibrary.h"

using namespace std;

WordManager::WordManager() {
    cout << "Word manager created!\n";
}

WordManager::WordManager(string path) {
    loadWords(path);
    cout << "Word manager created!\n";
}

WordManager::~WordManager() {
    for (vector<Word>::iterator it = wordsToFind.begin(); it != wordsToFind.end(); ++it) {
        it->coords.clear();
    }
    wordsToFind.clear();
    for (vector<Word>::iterator it = wordsFound.begin(); it != wordsFound.end(); ++it) {
        it->coords.clear();
    }
    wordsFound.clear();
    cout << "Word manager destroyed.\n";
}

// Private

void WordManager::pushWord(string word, Vector2 startCoord, Vector2 endCoord){
    Word wordToPush;
    wordToPush.word = word;
    wordToPush.coords = getPositionsBetween(startCoord, endCoord);
    wordsToFind.push_back(wordToPush);
}

vector<Vector2> WordManager::getPositionsBetween(Vector2 start, Vector2 end) {
    vector<Vector2> positions;

    int dx = end.x - start.x;
    int dy = end.y - start.y;

    int stepX = (dx != 0) ? (dx / abs(dx)) : 0;
    int stepY = (dy != 0) ? (dy / abs(dy)) : 0;

    int steps = max(abs(dx), abs(dy));

    for (int i = 0; i <= steps; ++i) {
        Vector2 currentPosition = { start.x + i * stepX, start.y + i * stepY };
        positions.push_back(currentPosition);
    }

    return positions;
}

WordStatus WordManager::validateWord(string word) {
    for (vector<Word>::iterator it = wordsToFind.begin(); it != wordsToFind.end(); ++it) {
        if (Utils::upCase(it->word) == Utils::upCase(word)) {
            return WordStatus::CORRECT;
        }
    }
    for (vector<Word>::iterator it = wordsFound.begin(); it != wordsFound.end(); ++it) {
        if (Utils::upCase(it->word) == Utils::upCase(word)) {
            return WordStatus::ALREADY_FOUND;
        }
    }

    return WordStatus::INCORRECT;
}

void WordManager::setToFound(string word) {
    for (vector<Word>::iterator it = wordsToFind.begin(); it != wordsToFind.end();) {
        if (Utils::upCase(it->word) == Utils::upCase(word)) {
            wordsFound.push_back(*it);
            it = wordsToFind.erase(it); // I just learned erase actually returns the next iterator!!! :)
        }
        else { // Since we're modifying the container it's safer to increment inside the for's scope
            ++it;
        }
    }
}

// Public

void WordManager::loadWords(string path) {
    ifstream inputStream;

    try {
        inputStream.open(path);
        if (!inputStream) {
            throw ifstream::failure("File \"" + path + "\" not found ");
        }

        string line;

        while (getline(inputStream, line)) {
            if (inputStream.fail()) {
                throw ifstream::failure("An error occurred while reading the file! ");
            }

            string word;
            Vector2 startCoord;
            Vector2 endCoord;
            // Parsing
            int openBracket = line.find('[');
            int closeBracket = line.find(']');

            string positions = line.substr(openBracket + 1, closeBracket - openBracket - 1);

            word = line.substr(closeBracket + 1);

            int dashPos = positions.find('-');

            string start = positions.substr(0, dashPos);
            string end = positions.substr(dashPos + 1);

            int colonPos = start.find(':');
            startCoord.x = stoi(start.substr(0, colonPos)) - 1;
            startCoord.y = stoi(start.substr(colonPos + 1)) - 1;

            colonPos = end.find(':');
            endCoord.x = stoi(end.substr(0, colonPos)) - 1;
            endCoord.y = stoi(end.substr(colonPos + 1)) - 1;
            //
            pushWord(word, startCoord, endCoord);
        }
        cout << wordsToFind.size() << " words were loaded successfully!";
        inputStream.close();
    }
    catch (ifstream::failure& exception) {
        cout << "An exception ocurred due to: " << exception.what() << "\n\n";

        if (inputStream.is_open())
            inputStream.close();
    }
}

int WordManager::getWordsToFindCount() {
    return wordsToFind.size();
}

int WordManager::getWordsFoundCount() {
    return wordsFound.size();
}

vector<Word> WordManager::getWordsFound() {
    return wordsFound;
}

bool WordManager::handleWord(string word) {
    if (word == "") return false; // We just ignore it if the string is empty

    switch (validateWord(word))
    {
    case WordStatus::INCORRECT:
        setForegroundColor(Color::LRED);
        cout << "I'm sorry but the word \"" << word << "\" is NOT part of this puzzle.\n";
        setForegroundColor(Color::WHITE);
        return false;
        break;
    case WordStatus::CORRECT:
        setToFound(word); // We add it to the found vector if it's valid
        setForegroundColor(Color::LGREEN);
        cout << "Congratulations, you found the word \"" << Utils::upCase(word) << "\"!!!\n";
        setForegroundColor(Color::WHITE);
        return true; // We want to return true only if the word is correct, the enum is mainly for accurate feedback
        break;
    case WordStatus::ALREADY_FOUND:
        setForegroundColor(Color::YELLOW);
        cout << "You already found this word bud. :)\n";
        setForegroundColor(Color::WHITE);
        return false;
        break;
    default:
        return false;
        break;
    }
}

void WordManager::printFoundWords() {
    for (vector<Word>::iterator it = wordsFound.begin(); it != wordsFound.end(); ++it) {
        setForegroundColor(Color::YELLOW);
        cout << it->word << "\n";
        setForegroundColor(Color::WHITE);
    }
}
