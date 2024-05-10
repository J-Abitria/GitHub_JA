#pragma once
#include "Node.hpp"

class Day {
public:
	Day() {
		this->name = "";
		this->listHead = nullptr;
	}

	Day(string n, Node* head) {
		this->name = n;
		this->listHead = head;
	}

	Day(Day& d) {
		this->name = d.name;
		this->listHead = d.listHead;
	}

	~Day() {

	}

	Node* getHead() { return this->listHead; }
	void setName(string newName) { this->name = newName; }

	void insertInOrder(Data newData);
	Data removeFront();
private:
	string name;
	Node* listHead;
};