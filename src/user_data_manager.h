#pragma once

#include <iostream>
#include <vector>
#include <list>

struct MatchData {
	std::string themeName;
	int amountTimesPlayed;
	float completion;
};

struct UserData {
	std::string userName;
	std::vector<MatchData> gamesPlayed;
};

class UserDataManager {
private:
	static std::list<UserData> users;
	static UserData loadedUser;
	static bool loggedIn;
	
	static void saveUsers();
	static void updateUser(UserData user);
	static UserData fetchData(std::string userName);
	static bool userExists(std::string userName);
public:
	static MatchData fetchMatchData(std::string themeName);
	static void pushMatchData(MatchData game);
	static void loadUsers();
	static void login(std::string userName);
	static void logout();

	static void printStatics();
};