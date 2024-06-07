#include <iostream>
#include <fstream>
#include <vector>

using std::string;
using std::vector;

class Move {
public:
	Move() {
		this->board = "";
		this->root = 0;
		this->branch = 0;
		this->move = 0;
	}

	Move(string board, int r, int b, int m) {
		this->board = board;
		this->root = r;
		this->branch = b;
		this->move = m;
	}

	Move(Move& m) {
		this->board = m.board;
		this->root = m.root;
		this->branch = m.branch;
		this->move = m.move;
	}


private:
	string board;
	int root;
	int branch;
	int move;
};