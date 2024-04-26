#pragma once
#include "Enode.hpp"

template <class T>
class List
{
public:
	List();

	void insert(T& data);

	void del(Node<T>* p);

	void del();



private:

	Node<T>* head;

	// we're using the private version of insert to allow for procedural
	// abstraction for the public interface; we don't want to show
	// that we're using pointers for our design; someone using our
	// template doesn't need to know specifically how the tree was developed, just
	// that to insert you need to specify the data

	//void preorderTraversal(Node<T>* pTree);

};

template <class T>
void List<T>::insert(T& data) {

	Node<T>* newnode = new Node<T>(data);
	if (newnode != NULL) {
		//puting newdTE INTO NEW NODE

		newnode->setnext(NULL);


		if (head == NULL) {

			head = newnode;
		}
		else {
			newnode->setnext(head);
			head = newnode;
		}

	}
}
