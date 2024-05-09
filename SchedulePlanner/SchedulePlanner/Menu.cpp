#include "Menu.hpp"

void Menu::runApp() {
	this->populateWeek();
	this->viewMenu();
}

void Menu::viewMenu() {
	cout << "1. Load from file" << endl;
	cout << "2. Save to file" << endl;
	cout << "3. View your schedule" << endl;
	cout << "4. Add an event" << endl;
	cout << "5. Change an event" << endl;
}

void Menu::populateWeek() {
	this->week[0].setName("Monday");
	this->week[1].setName("Tuesday");
	this->week[2].setName("Wednesday");
	this->week[3].setName("Thursday");
	this->week[4].setName("Friday");
	this->week[5].setName("Saturday");
	this->week[6].setName("Sunday");
}