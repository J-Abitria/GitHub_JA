#include "Menu.hpp"

void Menu::runApp() {
	int selection = 0;
	this->populateWeek();

	do {
		this->viewMenu();
		cin >> selection;
		if (selection > 0 && selection < 6) {
			this->runSelection(selection);
		}
	} while (selection != 0);
}

void Menu::viewMenu() {
	cout << "1. Load from file" << endl;
	cout << "2. Save to file" << endl;
	cout << "3. View your schedule" << endl;
	cout << "4. Add an event" << endl;
	cout << "5. Change an event" << endl;
	cout << "0. Exit" << endl;
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

void Menu::runSelection(int selection) {
	switch (selection) {
	case 1:
		this->loadData();
		cout << "Load successful." << endl;
		break;
	case 2:
		this->saveData();
		cout << "Save successful." << endl;
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	}
	system("pause");
	system("cls");
}

void Menu::loadData() {
	ifstream input("data.csv");
	string line = "";
	Data parsedInfo;
	int idx = 0, reference = 0;
	getline(input, line);
	getline(input, line);

	while (line.size() > 0) {
		idx = stoi(this->readToCharacter(line, reference));
		parsedInfo.setHour(stoi(this->readToCharacter(line, reference)));
		parsedInfo.setMinutes(stoi(this->readToCharacter(line, reference)));
		parsedInfo.setEvent(this->readToCharacter(line, reference));
		this->week[idx].insertInOrder(parsedInfo);
		reference = 0;
		getline(input, line);
	}

	input.close();
}

void Menu::saveData() {
	ofstream output("data.csv");
	Data extractedInfo;

	output << "Day of Week (0-6),Event Hour,Event Minutes,Event Name" << endl;
	for (int i = 0; i < 6; i++) {
		while (this->week[i].getHead() != nullptr) {
			output << i << ",";
			extractedInfo = this->week[i].removeFront();
			output << extractedInfo;
			output << endl;
		}
	}

	output.close();
}

string Menu::readToCharacter(string line, int& reference) {
	int idx = reference;
	bool reading = true;
	string segment = "";

	do {
		if ((line[idx] != ',' && line[idx] != '\n') && line[idx] != '\0') {
			segment += line[idx];
			idx++;
		}
		else {
			reading = false;
			reference = idx + 1;
		}
	} while (reading);

	return segment;
}