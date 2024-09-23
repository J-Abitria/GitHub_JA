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
		this->startHour = 0;
		this->startMinutes = 0;
		this->endHour = 0;
		this->endMinutes = 0;
		this->event = "";
	}

	Data(int sh, int sm, int eh, int em, string e) {
		this->startHour = sh;
		this->startMinutes = sm;
		this->endHour = eh;
		this->endMinutes = em;
		this->event = e;
	}

	Data(const Data& d) {
		this->startHour = d.startHour;
		this->startMinutes = d.startMinutes;
		this->endHour = d.endHour;
		this->endMinutes = d.endMinutes;
		this->event = d.event;
	}

	~Data() {

	}

	int getStartHour() const { return this->startHour; }
	int getStartMinutes() const { return this->startMinutes; }
	int getEndHour() const { return this->endHour; }
	int getEndMinutes() const { return this->endMinutes; }
	string getEvent() const { return this->event;  }
	void setStartHour(int newHour) { this->startHour = newHour; }
	void setStartMinutes(int newMinutes) { this->startMinutes = newMinutes; }
	void setEndHour(int newEndHour) { this->endHour = newEndHour; }
	void setEndMinutes(int newEndMinutes) { this->endMinutes = newEndMinutes; }
	void setEvent(string newEvent) { this->event = newEvent; }
private:
	int startHour;
	int startMinutes;
	int endHour;
	int endMinutes;
	string event;
};

inline ofstream& operator<< (ofstream& lhs, Data rhs) {
	if (rhs.getStartHour() < 10) { lhs << "0" << rhs.getStartHour() << ","; }
	else { lhs << rhs.getStartHour() << ","; }

	if (rhs.getStartMinutes() < 10) { lhs << "0" << rhs.getStartMinutes() << ","; }
	else { lhs << rhs.getStartMinutes() << ","; }

	if (rhs.getEndHour() < 10) { lhs << "0" << rhs.getEndHour() << ","; }
	else { lhs << rhs.getEndHour() << ",";  }

	if (rhs.getEndMinutes() < 10) { lhs << "0" << rhs.getEndMinutes() << ","; }
	else { lhs << rhs.getEndMinutes() << ","; }

	lhs << rhs.getEvent();

	return lhs;
}
