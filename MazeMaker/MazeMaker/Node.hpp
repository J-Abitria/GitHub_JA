#pragma once
#include "Tile.hpp"

class Node {
public:
	Node();
	Node(Tile t);

	Tile getTile() { return this->t; }
	Node* getNext() { return this->pNext; }
	void setTile(Tile newT) { this->t = newT; }
	void setNext(Node* newNext) { this->pNext = newNext; }
private:
	Tile t;
	Node* pNext;
};