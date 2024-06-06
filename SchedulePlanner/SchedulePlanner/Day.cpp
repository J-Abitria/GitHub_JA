#include "Day.hpp"

void Day::insertInOrder(Data newData) {
	Node* pMem = new Node(newData);

	if (this->listHead == nullptr) {
		this->listHead = pMem;
	}
	else {
		Node* pPrev = this->listHead, *pCur = this->listHead->getNext();
		int curTime = pPrev->getData().getStartHour() * 60 + pPrev->getData().getStartMinutes(),
			memTime = pMem->getData().getStartHour() * 60 + pMem->getData().getStartMinutes();
		bool added = false;
		if (memTime < curTime) {
			pMem->setNext(pPrev);
			this->listHead = pMem;
			added = true;
		}
		else {
			while (pCur != nullptr && !added) {
				curTime = pCur->getData().getStartHour() * 60 + pPrev->getData().getStartMinutes();
				if (memTime < curTime) {
					pMem->setNext(pCur);
					pPrev->setNext(pMem);
					added = true;
				}
				else {
					pCur = pCur->getNext();
					pPrev = pPrev->getNext();
				}
			}
			if (!added) { pPrev->setNext(pMem); }
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

bool Day::removeByName(string name) {
	Node* pPrev = this->listHead, * pCur = pPrev->getNext();

	if (pPrev->getData().getEvent() == name) {
		this->listHead = pCur;
		delete pPrev;
		return true;
	}

	while (pCur != nullptr) {
		if (pCur->getData().getEvent() == name) {
			pPrev->setNext(pCur->getNext());
			delete pCur;
			return true;
		}
		pCur = pCur->getNext();
		pPrev = pPrev->getNext();
	}
	return false;
}