#include "Node.hpp"

Node::Node() {
	
}

Node::Node(Tile t) {
	this->t = t;
	this->pNext = nullptr;
}

