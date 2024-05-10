#pragma once
#include "Data.hpp"

class Node {
public:
	Node(Data e) {
		this->eventInfo = e;
		this->pNext = nullptr;
	}

	Node(Node*& n) {
		this->eventInfo = n->eventInfo;
		this->pNext = n->pNext;
	}

	~Node() {

	}

	Data getData() { return this->eventInfo; }
	Node* getNext() { return this->pNext; }
	void setNext(Node* newNext) { this->pNext = newNext; }
private:
	Node* pNext;
	Data eventInfo;
};