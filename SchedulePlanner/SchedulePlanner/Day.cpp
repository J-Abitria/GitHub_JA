#include "Day.hpp"

void Day::insertInOrder(Data newData) {
	Node* pMem = new Node(newData);

	if (this->listHead == nullptr) {
		this->listHead = pMem;
	}
	else {
		Node* pCur = this->listHead;
		while (pCur != nullptr) {
			
		}
	}
}