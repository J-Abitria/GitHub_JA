#pragma once
#include <iostream>
#include <string>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;

class Data {
public:
	Data() {
		this->hour = 0;
		this->minutes = 0;
		this->event = "";
		this->description = "";
	}

	Data(int h, int m, string e, string d) {
		this->hour = h;
		this->minutes = m;
		this->event = e;
		this->description = d;
	}

	Data(Data& d) {
		this->hour = d.hour;
		this->minutes = d.minutes;
		this->event = d.event;
		this->description = d.description;
	}

	~Data() {

	}

	int getHour() { return this->hour; }
	int getMinutes() { return this->minutes; }
	string getEvent() { return this->event;  }
	string getDescription() { return this->description; }
	void setHour(int newHour) { this->hour = newHour; }
	void setMinutes(int newMinutes) { this->minutes = newMinutes; }
	void setEvent(string newEvent) { this->event = newEvent; }
	void setDescription(string newDescription) { this->description = newDescription;  }
private:
	int hour;
	int minutes;
	string event;
	string description;
};