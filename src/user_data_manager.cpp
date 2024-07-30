#include "user_data_manager.h"

#include <fstream>
#include <cstdio>

#include "AwesomeLibrary.h"
#include "utils.h"

using namespace std;

// Private

list<UserData> UserDataManager::users;
UserData UserDataManager::loadedUser;
bool UserDataManager::loggedIn = false;

void UserDataManager::saveUsers() {
	try {
		ofstream outputStream("users.dat", ios::out | ios::binary);

		if (!outputStream)
			throw ofstream::failure("Data could not be saved");

		int userCount = users.size();
		outputStream.write(reinterpret_cast<char*>(&userCount), sizeof(userCount));

		for (list<UserData>::iterator it = users.begin(); it != users.end(); ++it) {
			// De-serialization :(
			// User info
			int userNameLength = it->userName.size();
			outputStream.write(reinterpret_cast<char*>(&userNameLength), sizeof(userNameLength));
			outputStream.write(it->userName.c_str(), userNameLength);

			// Match info
			int gamesCount = it->gamesPlayed.size();
			outputStream.write(reinterpret_cast<char*>(&gamesCount), sizeof(gamesCount));
			for (int i = 0; i < gamesCount; ++i) {
				const MatchData& match = it->gamesPlayed[i];

				int themeNameLength = match.themeName.size();
				outputStream.write(reinterpret_cast<char*>(&themeNameLength), sizeof(themeNameLength));
				outputStream.write(match.themeName.c_str(), themeNameLength);

				outputStream.write(reinterpret_cast<const char*>(&match.amountTimesPlayed), sizeof(match.amountTimesPlayed));
				outputStream.write(reinterpret_cast<const char*>(&match.completion), sizeof(match.completion));
			}
		}

		cout << "Data saved successfully!\n";
		outputStream.close();
	}
	catch (const ofstream::failure& exception) {
		cout << "An exception occurred due to: " << exception.what() << "\n";
	}
}

void UserDataManager::updateUser(UserData user) {
	for (list<UserData>::iterator it = users.begin(); it != users.end(); ++it) {
		if (it->userName == user.userName) {
			it->gamesPlayed = user.gamesPlayed;
			return;
		}
	}
	users.push_back(user);
}

UserData UserDataManager::fetchData(string userName) {
	UserData data;
	data.userName = "null";
	for (list<UserData>::iterator it = users.begin(); it != users.end(); ++it) {
		if (it->userName == userName) {
			data = *it;
			return data;
		}
	}
	return data;
}

bool UserDataManager::userExists(string userName) {
	for (list<UserData>::iterator it = users.begin(); it != users.end(); ++it) {
		if (it->userName == userName) {
			return true;
		}
	}
	return false;
}

// Public

MatchData UserDataManager::fetchMatchData(string themeName) {
	for (vector<MatchData>::iterator it = loadedUser.gamesPlayed.begin(); it != loadedUser.gamesPlayed.end(); ++it) {
		if (it->themeName == themeName) return *it;
	}
	MatchData md;
	md.themeName = themeName;
	md.amountTimesPlayed = 0;
	md.completion = 0.0f;
	return md;
}

void  UserDataManager::pushMatchData(MatchData game) {
	if (loggedIn) {
		for (vector<MatchData>::iterator it = loadedUser.gamesPlayed.begin(); it != loadedUser.gamesPlayed.end(); ++it) {
			if (game.themeName == it->themeName) {
				*it = game;
				return;
			}
		}
		loadedUser.gamesPlayed.push_back(game);
	}
}

void UserDataManager::loadUsers() {
	try {
		ifstream inputStream("users.dat", ios::in | ios::binary);

		if (!inputStream)
			throw ifstream::failure("There is no previous data saved in the specified path");

		int userCount;
		inputStream.read(reinterpret_cast<char*>(&userCount), sizeof(userCount));

		users.clear();

		for (int i = 0; i < userCount; ++i) {
			UserData user;
			// Serialization :)
			// User info
			int userNameLength;
			inputStream.read(reinterpret_cast<char*>(&userNameLength), sizeof(userNameLength));
			user.userName.resize(userNameLength);
			inputStream.read(&user.userName[0], userNameLength);

			// Match info
			int gamesCount;
			inputStream.read(reinterpret_cast<char*>(&gamesCount), sizeof(gamesCount));
			user.gamesPlayed.resize(gamesCount);
			for (int j = 0; j < gamesCount; ++j) {
				MatchData& match = user.gamesPlayed[j];

				int themeNameLength;
				inputStream.read(reinterpret_cast<char*>(&themeNameLength), sizeof(themeNameLength));
				match.themeName.resize(themeNameLength);
				inputStream.read(&match.themeName[0], themeNameLength);

				inputStream.read(reinterpret_cast<char*>(&match.amountTimesPlayed), sizeof(match.amountTimesPlayed));
				inputStream.read(reinterpret_cast<char*>(&match.completion), sizeof(match.completion));
			}

			users.push_back(user);
		}

		cout << "Data loaded successfully!\n";
		inputStream.close();
	}
	catch (const ifstream::failure& exception) {
		cout << "An exception occurred due to: " << exception.what() << "\n";
	}
}

void UserDataManager::login(string userName) {
	string myUserName = Utils::upCase(userName);
	if (loggedIn) logout();
	if (!userExists(myUserName)) {
		loadedUser.userName = myUserName;
		updateUser(loadedUser);
	}
	else {
		loadedUser = fetchData(myUserName);
	}
	loggedIn = true;
}

void UserDataManager::logout() {
	if (loggedIn) {
		updateUser(loadedUser);
		saveUsers(); // Data is updated and saved on logout.
		loadedUser.gamesPlayed.clear();
		loggedIn = false;
	}
}

void UserDataManager::printStatics() {
	if (users.empty()) {
		cout << "No user data has been recorded.\n";
	}
	else {
		cout << "Users recorded in this machine:\n";
		for (list<UserData>::iterator it = users.begin(); it != users.end(); ++it) {
			cout << "\n";
			cout << "Name: " << it->userName << "\n";
			cout << "Puzzles Played:\n";
			if (it->gamesPlayed.empty()) {
				setForegroundColor(Color::LRED);
				cout << "User has not played any puzzles yet.\n";
				setForegroundColor(Color::WHITE);
			}
			else {
				for (vector<MatchData>::iterator _it = it->gamesPlayed.begin(); _it != it->gamesPlayed.end(); ++_it) {
					cout << "\n";
					if (_it->completion == 100.0f) {
						setForegroundColor(Color::LGREEN);
					}
					cout << "Puzzle Name: " << _it->themeName << "\n";
					cout << "Times Played: " << _it->amountTimesPlayed << "\n";
					cout << "Completion: " << _it->completion << "%\n";
					setForegroundColor(Color::WHITE);
				}
			}
			cout << "________________________________________\n";
		}
	}
}
