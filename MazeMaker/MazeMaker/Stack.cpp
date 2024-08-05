#include "Stack.hpp"

Stack::Stack() {
	this->pTop = nullptr;
}

Stack::Stack(Node* top) {
	this->pTop = top;
}

void Stack::push(Node* newNode) {
	if (this->pTop != nullptr) {
		newNode->setNext(this->pTop);
	}
	this->pTop = newNode;
}

void Stack::pop() {
	Node* temp = this->pTop;
	if (this->pTop->getNext() != nullptr) {
		this->pTop = this->pTop->getNext();
	}
	else {
		this->pTop = nullptr;
	}
	delete temp;
}