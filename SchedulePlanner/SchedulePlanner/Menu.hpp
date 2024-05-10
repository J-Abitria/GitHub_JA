#pragma once
#include "Day.hpp"

class Menu {
public:
	Menu() {

	}

	~Menu() {

	}

	void runApp();
private:
	void populateWeek();
	void viewMenu();
	void runSelection(int selection);
	void loadData();
	void saveData();
	string readToCharacter(string line, int& reference);
	Day week[7];
};