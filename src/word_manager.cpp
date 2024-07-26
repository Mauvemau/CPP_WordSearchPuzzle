#include "word_manager.h"

#include <fstream>
#include <cmath>

using namespace std;

WordManager::WordManager(std::string path) {
    loadWords(path);
    cout << "Word manager created!\n";
}

WordManager::~WordManager() {
    for (int i = 0; i < static_cast<int>(words.size()); i++) {
        words[i].coords.clear();
    }
    words.clear();
    cout << "Board manager deleted.\n";
}

// Private

void WordManager::pushWord(std::string word, Vector2 startCoord, Vector2 endCoord){
    Word wordToPush;
    wordToPush.word = word;
    wordToPush.coords = getPositionsBetween(startCoord, endCoord);
    words.push_back(wordToPush);
}

void WordManager::loadWords(std::string path) {
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
        cout << "File loaded successfully!\n";
        inputStream.close();
    }
    catch (ifstream::failure& exception) {
        cout << "An exception ocurred due to: " << exception.what() << "\n\n";

        if (inputStream.is_open())
            inputStream.close();
    }
}

vector<Vector2> WordManager::getPositionsBetween(Vector2 start, Vector2 end) {
    vector<Vector2> positions;

    int dx = end.x - start.x;
    int dy = end.y - start.y;

    int stepX = (dx != 0) ? (dx / std::abs(dx)) : 0;
    int stepY = (dy != 0) ? (dy / std::abs(dy)) : 0;

    int steps = std::max(std::abs(dx), std::abs(dy));

    for (int i = 0; i <= steps; ++i) {
        Vector2 currentPosition = { start.x + i * stepX, start.y + i * stepY };
        positions.push_back(currentPosition);
    }

    return positions;
}

// Public

void WordManager::print() {
    for (int i = 0; i < static_cast<int>(words.size()); i++) {
        cout << words[i].word << "\n";
        for (int j = 0; j < static_cast<int>(words[i].coords.size()); j++) {
            cout << words[i].coords[j].x << ";" << words[i].coords[j].y << " ";
        }
        cout << "\n";
    }
}
