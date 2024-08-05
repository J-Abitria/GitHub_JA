#pragma once
#include "Node.hpp"

class Stack {
public:
	Stack();
	Stack(Node* top);

	void push(Node* newNode);
	void pop();
	bool isEmpty() { return this->pTop == nullptr; }
	Node* peek() { return this->pTop; }
private:
	Node* pTop;
};