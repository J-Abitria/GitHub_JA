#include "Game.hpp"

void Game::populateTree() {
	ifstream input("Board1.csv");
	string parsedLine;
	int idx;
	Move m;
	Tree boardOne;
	getline(input, parsedLine);

	while (!input.eof()) {
		idx = 0;
		getline(input, parsedLine);
		m.setBoard(readToCharacter(parsedLine, idx));
		m.setID(stoi(readToCharacter(parsedLine, idx)));

		TreeNode* t = new TreeNode(m);
		boardOne.insertInTree(t);
	}
}

// Reimplemented function from various projects.
string Game::readToCharacter(string line, int& reference) {
	int idx = reference;
	bool reading = true;
	string segment = "";

	do {
		if ((line[idx] != ',' && line[idx] != '\n') && line[idx] != '\0') {
			segment += line[idx];
			idx++;
		}
		else {
			reading = false;
			reference = idx + 1;
		}
	} while (reading);

	return segment;
}