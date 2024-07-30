#include "menu.h"

#include "user_data_manager.h"
#include "AwesomeLibrary.h"

using namespace std;

Menu::Menu() {
	game = new Game();
	exit = false;
	cout << "Menu created.\n";
}

Menu::~Menu() {
	delete game;
	cout << "Menu destroyed.\n";
}

// Private

void Menu::gameSelectMenu() {
	int input;
	bool goBack = false;
	do {
		clearScreen();
		cout << "Please use the numbers on your keyboard to select one of the following available puzzles:\n";
		int i = 1;
		for (vector<GameData>::iterator it = loadableGames.begin(); it != loadableGames.end(); ++it) {
			cout << i << ". " << it->displayName << "\n";
			cout << "Size: " << it->size.x << "x" << it->size.y << "\n";
			cout << "Amount of words: " << it->amountWords << "\n";
			cout << "-\n";
			i++;
		}

		cout << "Input > ";
		input = getKey(true);
		if (KEY_ESC == input) {
			goBack = true;
		}else {
			int index = input - static_cast<int>('0');
			index--;
			if (index > -1 && index < static_cast<int>(loadableGames.size())) {
				game->load(loadableGames[index].id, loadableGames[index].displayName);
				game->save();
			}
		}
	} while (!goBack);
}

void Menu::userMenu() {
	string userName;
	cout << "Please input your name. (or press ESC to cancel)\n";
	cout << "Input > ";
	do {
		userName = Utils::customCharacterInput();
	} while (userName.size() < 1);
	if (userName != MAGIC_STRING) {
		clearScreen();
		UserDataManager::login(userName);
		gameSelectMenu();
	}
}

void Menu::update() {
	int input;
	do {
		clearScreen();
		cout << "Use the numbers on your keyboard to select one of the following options:\n";
		cout << "1. Select Puzzle\n";
		cout << "2. See User Statics\n";
		cout << "3. Exit Program\n";

		cout << "Input > ";
		input = getKey(true);

		switch (static_cast<char>(input))
		{
		case '1':
			clearScreen();
			userMenu(); // Login to an user
			UserDataManager::logout(); // We logout from our user after leaving the game
			break;
		case '2':
			clearScreen();
			UserDataManager::printStatics();
			cout << "\nPress any key to return...\n";
			getKey();
			break;
		case '3':
			exit = true;
			break;
		case static_cast<char>(KEY_ESC):
			exit = true;
			break;
		default:
			break;
		}
	} while (!exit);
	clearScreen();
}

// Public

void Menu::addGame(GameData data) {
	loadableGames.push_back(data);
}

void Menu::run() {
	UserDataManager::loadUsers();
	update();
}