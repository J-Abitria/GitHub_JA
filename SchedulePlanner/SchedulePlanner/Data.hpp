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
	}

	Data(int h, int m, string e, string d) {
		this->hour = h;
		this->minutes = m;
		this->event = e;
	}

	Data(Data& d) {
		this->hour = d.hour;
		this->minutes = d.minutes;
		this->event = d.event;
	}

	~Data() {

	}

	int getHour() { return this->hour; }
	int getMinutes() { return this->minutes; }
	string getEvent() { return this->event;  }
	void setHour(int newHour) { this->hour = newHour; }
	void setMinutes(int newMinutes) { this->minutes = newMinutes; }
	void setEvent(string newEvent) { this->event = newEvent; }
private:
	int hour;
	int minutes;
	string event;
};

inline ofstream& operator<< (ofstream& lhs, Data rhs) {
	if (rhs.getHour() < 10) {
		lhs << "0" << rhs.getHour() << ",";
	}
	else {
		lhs << rhs.getHour() << ",";
	}
	if (rhs.getMinutes() < 10) {
		lhs << "0" << rhs.getMinutes() << ",";
	}
	else {
		lhs << rhs.getMinutes() << ",";
	}
	lhs << rhs.getEvent();

	return lhs;
}