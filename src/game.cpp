#include "game.h"

using namespace std;

Game::Game(){
    board = new Board();
    wm = new WordManager();
    finished = false;

    cout << "Game created.\n";
}

Game::~Game(){
    if(board)
        delete board;
    if(wm)
        delete wm;
    cout << "Game destroyed.\n";
}

// Private

void Game::colorFoundWordsOnBoard(std::vector<Word> wordsToColor, Color color) {
    while (!wordsToColor.empty()) {
        board->colorSlots(wordsToColor.back().coords, color);
        wordsToColor.pop_back();
    }
}

void Game::update(){
    do {
        clearScreen();
        string input;

        board->print();
        cout << "\n";
        cout << "Words left to find: " << wm->getWordsToFindCount() << "\n";
        if (wm->getWordsFoundCount() > 0) {
            cout << "Words Found:\n";
            wm->printFoundWords();
        }
        cout << "\n";
        cout << "Input > ";

       input = Utils::customCharacterInput();
       if (MAGIC_STRING == input) { // Manual exit condition
           finished = true;
       }
       else if(input != "") { // If the user doesn't input anything just ignore
           if (wm->handleWord(input)) {
               colorFoundWordsOnBoard(wm->getWordsFound(), Color::LGREEN);
           }
           getKey(true);
       }

    } while (!finished);
    // save statics
}

// Public

void Game::load(string name){
    board->load(name + ".txt");
    wm->loadWords(name + "_words.txt");
    cout << "\n";

    update();
}
