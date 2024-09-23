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
	void viewSchedule();
	void createEvent();
	void editEvent();
	void deleteMenu();
	string readToCharacter(string line, int& reference);
	int promptDay();
	void displayEvent(Data eventInfo);
	void editingMenu(Node* dataLocation);
	Day week[7];
};