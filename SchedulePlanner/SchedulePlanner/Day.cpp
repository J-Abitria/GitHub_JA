#include "Day.hpp"

void Day::insertInOrder(Data newData) {
	Node* pMem = new Node(newData);

	if (this->listHead == nullptr) {
		this->listHead = pMem;
	}
	else {
		Node* pCur = this->listHead;
		int curTime = pCur->getData().getHour() * 60 + pCur->getData().getMinutes(), memTime = pMem->getData().getHour() * 60 + pMem->getData().getMinutes();
		while (pCur != nullptr) {
			if (curTime < memTime) {
				pCur = pCur->getNext();
			}
			else {
				pMem->setNext(pCur->getNext());
				pCur->setNext(pMem);
			}
		}
	}
}

Data Day::removeFront() {
	Data removedInfo;

	if (this->listHead->getNext() == nullptr) {
		removedInfo = this->listHead->getData();
		this->listHead = nullptr;
	}
	else {
		Node* pTemp = this->listHead;
		removedInfo = pTemp->getData();
		this->listHead = this->listHead->getNext();
		delete pTemp;
	}

	return removedInfo;
}