#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::ifstream;

class Move {
public:
	Move() {
		this->board = "";
		this->ID = 0;
	}

	Move(string board, int i) {
		this->board = board;
		this->ID = i;
	}

	Move(Move& m) {
		this->board = m.board;
		this->ID = m.ID;
	}

	void setBoard(string newBoard) { this->board = newBoard; }
	void setID(int newID) { this->ID = newID; }
	string getBoard() { return this->board; }
	int getID() { return this->ID; }
private:
	string board;
	int ID;
};