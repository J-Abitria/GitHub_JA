#include "Day.hpp"

void Day::insertInOrder(Data newData) {
	Node* pMem = new Node(newData);

	if (this->listHead == nullptr) {
		this->listHead = pMem;
	}
	else {
		Node* pCur = this->listHead;
		int curTime = 0, memTime = pMem->getData().getHour() * 60 + pMem->getData().getMinutes();
		bool added = false;
		while (pCur != nullptr && !added) {
			curTime = pCur->getData().getHour() * 60 + pCur->getData().getMinutes();
			if (curTime < memTime) {
				if (pCur->getNext() != nullptr) {
					pCur = pCur->getNext();
				}
				else {
					pCur->setNext(pMem);
					added = true;
				}
			}
			else {
				pMem->setNext(pCur->getNext());
				pCur->setNext(pMem);
				added = true;
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