#pragma once
#include "Enemy.hpp"
template <class T>
class Node
{
public:
	Node(T da);

	T& getData();
	Node<T>* getnext() const;

	void setnext(Node* const newNext);



private:
	T mData;
	Node<T>* next;
};
template <class T>
Node<T>::Node(T da) {
	this->mData = da;
	this->next = nullptr;
}

template <class T>
T& Node<T>::getData() {
	return this->mData;
}
template <class T>
Node<T>* Node<T>::getnext() const {
	return this->next;
}
template <class T>
void Node<T>::setnext(Node* const newNext) {
	this->next = newNext;
}
