#pragma once
#include "Day.hpp"

class Menu {
public:
	Menu() {

	}

	~Menu() {

	}

	void runApp();
	void viewMenu();
private:
	void populateWeek();
	Day week[7];
};