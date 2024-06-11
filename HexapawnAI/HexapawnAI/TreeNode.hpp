#include "Move.hpp"

class TreeNode {
public:
	TreeNode() {

	}

	TreeNode(Move data) {
		this->data = data;
	}

	TreeNode(TreeNode& t) {
		this->children = t.children;
		this->data = t.data;
	}

	vector<TreeNode*> getChildren() const { return this->children; }
	Move getData() { return this->data; }
	void insertChild(TreeNode*& child) { children.push_back(child); }
private:
	vector<TreeNode*> children;
	Move data;
};