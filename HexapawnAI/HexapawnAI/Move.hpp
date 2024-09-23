#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::cin;
using std::endl;

class Move {
public:
	Move() {
		this->board = "";
		this->ID = 0;
		this->playable = true;
	}

	Move(string board, int i) {
		this->board = board;
		this->ID = i;
		this->playable = true;
	}

	Move(Move& m) {
		this->board = m.board;
		this->ID = m.ID;
		this->playable = m.playable;
	}

	void setBoard(string newBoard) { this->board = newBoard; }
	void setID(int newID) { this->ID = newID; }
	void disableMove() { this->playable = false; }
	string getBoard() const { return this->board; }
	int getID() const { return this->ID; }
	bool isPlayable() const { return this->playable; }
private:
	string board;
	int ID;
	bool playable;
};