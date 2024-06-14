#include "Move.hpp"

class TreeNode {
public:
	TreeNode() {

	}

	TreeNode(Move data) {
		this->data = data;
		this->playable = true;
	}

	TreeNode(TreeNode& t) {
		this->children = t.children;
		this->data = t.data;
		this->playable = true;
	}

	vector<TreeNode*> getChildren() const { return this->children; }
	Move getData() { return this->data; }
	void insertChild(TreeNode*& child) { children.push_back(child); }
private:
	vector<TreeNode*> children;
	Move data;
	bool playable;
};