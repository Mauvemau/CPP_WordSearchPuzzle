#include "AwesomeLibrary.h"

#include <iostream>

using namespace std;

int main() {
	int keyPress = 0;

	cout << "Press a key to display the key pressed!\nPress ESC to exit\n";

	do {
		if (keyPress > 0) {
			cout << "Key pressed: " << static_cast<char>(keyPress) << "\n";
		}
		keyPress = getKey();

		clearScreen();
	} while (keyPress != KEY_ESC);
	clearScreen();

	cout << "Press any key to exit the software.\n";
	getKey(true);
	return 0;
}