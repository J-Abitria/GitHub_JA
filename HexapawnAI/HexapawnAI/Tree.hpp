#include "TreeNode.hpp"

class Tree {
public:
	Tree() {
		this->treeHead = nullptr;
	}

	Tree(TreeNode* t) {
		this->treeHead = t;
	}

	Tree(Tree& t) {
		this->treeHead = t.treeHead;
	}

	TreeNode* getHead() const { return this->treeHead; }
	void insertInTree(TreeNode*& newNode);
private:
	TreeNode* treeHead;
};