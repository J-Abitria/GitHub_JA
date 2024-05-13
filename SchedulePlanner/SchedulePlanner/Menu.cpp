#include "Menu.hpp"

void Menu::runApp() {
	int selection = 0;
	this->populateWeek();

	do {
		this->viewMenu();
		cin >> selection;
		if (selection > 0 && selection < 7) {
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
	cout << "6. Delete event(s)" << endl;
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
		this->viewSchedule();
		break;
	case 4:
		this->createEvent();
		cout << "Added a new event." << endl;
		break;
	case 5:
		this->editEvent();
		break;
	case 6:
		this->deleteMenu();
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

void Menu::viewSchedule() {
	for (Day d : this->week) {
		cout << d.getName() << ":" << endl;
		Node* pCur = d.getHead();
		while (pCur != nullptr) {
			this->displayEvent(pCur->getData());

			pCur = pCur->getNext();
		}
	}
}

void Menu::createEvent() {
	int selection = 0, hour = 0, minutes = 0;
	string name;
	char confirm = '\0';
	
	selection = this->promptDay();

	do {
		system("cls");
		cout << "Name the event you wish to make (no spaces or commas!):" << endl;
		cin >> name;
		cout << "Is this correct? (Y/N) " << name << endl;
		cin >> confirm;
	} while (toupper(confirm) != 'Y');

	do {
		system("cls");
		cout << "Enter the time for the event (Format HH:MM)" << endl;
		cin >> hour >> confirm >> minutes;
		if ((hour > -1 && hour < 25) && (minutes > -1 && minutes < 60)) {
			cout << "Are these times correct? (Y/N) - Hour: " << hour << " Minutes: " << minutes << endl;
			cin >> confirm;
		}
		else {
			cout << "One of the inputted values is invalid." << endl;
			system("pause");
			confirm = 'N';
		}
	} while (toupper(confirm) != 'Y');

	Data newEvent(hour, minutes, name);
	this->week[selection].insertInOrder(newEvent);
}

void Menu::editEvent() {
	int idx = this->promptDay(), count = 0, selection = 0;
	Node* pCur = this->week[idx].getHead();

	if (pCur != nullptr) {
		while (pCur != nullptr) {
			count++;
			cout << count << ". ";
			this->displayEvent(pCur->getData());

			pCur = pCur->getNext();
		}

		do {
			cout << "Enter the number next to the event you want to edit." << endl;
			cin >> selection;

			if (selection < 0 || selection > count) {
				cout << "That input is invalid." << endl;
				system("pause");
			}
		} while (selection < 1 || selection > count);

		pCur = this->week[idx].getHead();
		for (int i = 0; i < selection - 1; i++) {
			pCur = pCur->getNext();
		}
		this->editingMenu(pCur);
	}
	else {
		cout << "There are no events to edit!" << endl;
	}
}

void Menu::deleteMenu() {
	int idx = this->promptDay(), selection = 0;
	system("cls");
	cout << "1. Delete a single event from the day" << endl;
	cout << "2. Clear every event in the day" << endl;
	cin >> selection;

	if (selection == 2) {
		while (this->week[idx].getHead() != nullptr) {
			this->week[idx].removeFront();
		}
		cout << "Successfully cleared every event." << endl;
	}
	else {
		Node* pCur = this->week[idx].getHead();
		string deletedEvent = "";

		while (pCur != nullptr) {
			this->displayEvent(pCur->getData());
			pCur = pCur->getNext();
		}
		cout << "Please enter the name of the event you want to delete (case-sensitive, spell exactly)" << endl;
		cin >> deletedEvent;

		if (!this->week[idx].removeByName(deletedEvent)) {
			cout << "Could not find an event of that name." << endl;
		}
		else {
			cout << "Successfully removed that event." << endl;
		}
	}
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

int Menu::promptDay() {
	int selection = 0;
	char confirm = '\0';

	do {
		system("cls");
		cout << "Enter a number for the day you want to access (1-7, 1 is Monday, days are in order with 7 being Sunday):" << endl;
		cin >> selection;
		if (selection < 1 || selection > 7) {
			cout << "That is not a valid day." << endl;
			system("pause");
		}
		else {
			cout << "You entered " << this->week[selection - 1].getName() << ". Is this correct? (Y/N)" << endl;
			cin >> confirm;
		}
	} while (toupper(confirm) != 'Y');

	return selection - 1;
}

void Menu::displayEvent(Data eventInfo) {
	cout << eventInfo.getEvent() << " - ";
	if (eventInfo.getHour() < 10) {
		cout << "0" << eventInfo.getHour() << ":";
	}
	else {
		cout << eventInfo.getHour() << ":";
	}
	if (eventInfo.getMinutes() < 10) {
		cout << "0" << eventInfo.getMinutes() << endl;
	}
	else {
		cout << eventInfo.getMinutes() << endl;
	}
}

void Menu::editingMenu(Node* dataLocation) {
	int selection = 0, hour = 0, minutes = 0;
	string newName = "";
	char buffer = '\0';
	do {
		system("cls");
		this->displayEvent(dataLocation->getData());
		cout << "Enter the number of the field to edit." << endl;
		cout << "1. Name" << endl;
		cout << "2. Time" << endl;
		cin >> selection;

		if (selection < 1 || selection > 2) {
			cout << "This input is invalid." << endl;
		}
		else {
			switch (selection) {
			case 1:
				cout << "Enter the new name for the event." << endl;
				cin >> newName;
				dataLocation->getDataRef().setEvent(newName);
				break;
			case 2:
				cout << "Enter the new time for the event (Format HH:MM)" << endl;
				cin >> hour >> buffer >> minutes;
				if ((hour >= 0 && hour < 24) && (minutes >= 0 && minutes < 60)) {
					dataLocation->getDataRef().setHour(hour);
					dataLocation->getDataRef().setMinutes(minutes);
				}
				else {
					cout << "This input is invalid." << endl;
					system("pause");
				}
				break;
			}
		}
		system("cls");
		this->displayEvent(dataLocation->getData());
		cout << "Is this correct? (Y/N)" << endl;
		cin >> buffer;
	} while (toupper(buffer) != 'Y');
}