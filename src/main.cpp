#include "menu.h"

int main() {
	Menu* menu = new Menu();

	GameData animals;
	animals.id = "animals";
	animals.displayName = "Animal Names";
	animals.size = { 10, 10 };
	animals.amountWords = 8;
	GameData computers;
	computers.id = "computers";
	computers.displayName = "Computer Parts";
	computers.size = { 10, 10 };
	computers.amountWords = 11;
	GameData cars;
	cars.id = "cars";
	cars.displayName = "Car Brands";
	cars.size = { 15, 15 };
	cars.amountWords = 12;

	menu->addGame(animals);
	menu->addGame(computers);
	menu->addGame(cars);

	menu->run();

	delete menu;
	return 0;
}
