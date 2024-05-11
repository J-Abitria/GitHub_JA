#pragma once
#include "Data.hpp"

class Node {
public:
	Node(Data e) {
		this->eventInfo = e;
		this->pNext = nullptr;
	}

	Node(const Node*& n) {
		this->eventInfo = n->eventInfo;
		this->pNext = n->pNext;
	}

	~Node() {

	}

	Data getData() const { return this->eventInfo; }
	Node* getNext() const { return this->pNext; }
	void setNext(Node* newNext) { this->pNext = newNext; }
private:
	Node* pNext;
	Data eventInfo;
};