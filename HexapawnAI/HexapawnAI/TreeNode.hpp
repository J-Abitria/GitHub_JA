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
	Move& getDataRef() { return this->data; }
	void insertChild(TreeNode*& child) { children.push_back(child); }
	void printChildren() {
		for (TreeNode* t : this->children) {
			cout << t->getData().getBoard() << " - " << t->getData().getID() << endl;
		}
	}
private:
	vector<TreeNode*> children;
	Move data;
	bool playable;
};