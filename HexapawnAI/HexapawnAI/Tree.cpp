#include "Tree.hpp"

void Tree::insertInTree(TreeNode*& newNode) {
	int boardID = newNode->getData().getID();
	TreeNode* curNode = this->treeHead;
	if (boardID == 0) {
		this->treeHead = newNode;
	}
	else {
		do {
			boardID /= 10;

			if (boardID < 10 && boardID > 0) {
				curNode->insertChild(newNode);
			}
			else {
				curNode = curNode->getChildren()[boardID % 10 - 1];
			}
		} while (boardID > 10);
	}
}