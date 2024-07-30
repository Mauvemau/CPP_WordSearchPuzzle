#include "game.h"

#include "user_data_manager.h"

using namespace std;

Game::Game(){
    board = new Board();
    wm = new WordManager();
    finished = false;

    cout << "Game created.\n";
}

Game::~Game(){
    delete board;
    delete wm;
    cout << "Game destroyed.\n";
}

// Private

void Game::colorFoundWordsOnBoard(vector<Word> wordsToColor, Color color) {
    while (!wordsToColor.empty()) {
        board->colorSlots(wordsToColor.back().coords, color);
        wordsToColor.pop_back();
    }
}

void Game::update(){
    do {
        clearScreen();
        string input;

        cout << themeName << "\n";
        board->print();
        if (wm->getWordsFoundCount() > 0) {
            cout << "Words Found:\n";
            wm->printFoundWords();
        }
        if (wm->getWordsToFindCount() > 0) { // If user has not won yet
            cout << "Words left to find: " << wm->getWordsToFindCount() << "\n";
            cout << "Input > ";
            input = Utils::customCharacterInput();
            if (MAGIC_STRING == input) { // Manual exit condition
                finished = true;
            }
            else if (input != "") { // If the user doesn't input anything just ignore
                if (wm->handleWord(input)) {
                    colorFoundWordsOnBoard(wm->getWordsFound(), Color::LGREEN);
                }
                getKey(true);
            }
        }
        else { // If user won
            setForegroundColor(Color::LGREEN);
            cout << "Congratulations! you found all the words for this puzzle!\n";
            setForegroundColor(Color::WHITE);
            cout << "Press ESC key to return to menu\n";
            int newInput = getKey(); // The other one is a string Input
            if (newInput == KEY_ESC) {
                finished = true;
            }
        }
    } while (!finished);
}

// Public

void Game::load(string name, string themeName){
    this->themeName = themeName;
    finished = false;

    board->load("puzzles/" + name + ".txt");
    wm->loadWords("puzzles/" + name + "_words.txt");
    cout << "\n";

    update();
}

void Game::save() {
    MatchData md = UserDataManager::fetchMatchData(themeName);
    int playCount = md.amountTimesPlayed + 1;
    int wordsFound = wm->getWordsFoundCount();
    int wordsLeft = wm->getWordsToFindCount();
    float completion;
    if (wordsFound + wordsLeft == 0) {
        completion = 0.0f;
    }else {
        completion = (static_cast<float>(wordsFound) / (wordsFound + wordsLeft)) * 100.0f;
    }
    md.themeName = themeName;
    md.amountTimesPlayed = playCount;
    if (md.completion < completion) {
        md.completion = completion;
    }

    UserDataManager::pushMatchData(md);
}
