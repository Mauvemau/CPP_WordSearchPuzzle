#include "game.h"

using namespace std;

Game::Game(){

}

Game::~Game(){
    if(board)
        delete board;
    if(wm)
        delete wm;
}

// Private

void Game::update(){
    cout << "\n";

    board->print();
    cout << "\n";
    wm->print();

    cout << "\n";
}

// Public

void Game::load(string name){
    board = new Board(name + ".txt");
    wm = new WordManager(name + "_words.txt");

    update();
}
