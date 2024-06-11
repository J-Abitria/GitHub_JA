#include "Game.hpp"

Game::Game() {
	for (int i = 0; i < 3; i++) {
		Pawn p(2, i);
		Pawn e(0, i);
		this->playerPawns[i] = p;
		this->enemyPawns[i] = e;
	}

	for (int i = 0; i < 6; i++) {
		if (i < 3) {
			this->legalPushes[i] = true;
		}
		this->legalCaptures[i] = false;
	}
}

void Game::playGame() {
	int pawnMove = 0;
	this->printBoard();
	cout << "Enter the number of the pawn you wish to move:" << endl;
	this->printOptions();
	cin >> pawnMove;
	if ((pawnMove > 0 && pawnMove < 4) && this->legalPushes[pawnMove - 1]) {
		this->playerPawns[pawnMove - 1].pushPawn();
		switch (pawnMove) {
		case 1:
			if (board1.getHead() == nullptr)
				this->populateTree(1);
			break;
		case 2:
			if (board2.getHead() == nullptr)
				this->populateTree(2);
			break;
		case 3:
			if (board3.getHead() == nullptr)
				this->populateTree(3);
			break;
		}
	}
	this->printBoard();
}

void Game::populateTree(int tree) {
	string fileName = "";
	switch (tree) {
	case 1:
		fileName = "Board1.csv";
		break;
	case 2:
		fileName = "Board2.csv";
		break;
	case 3:
		fileName = "Board3.csv";
		break;
	}

	ifstream input(fileName);
	string parsedLine;
	int idx;
	Move m;
	Tree board;
	getline(input, parsedLine);

	while (!input.eof()) {
		idx = 0;
		getline(input, parsedLine);
		m.setBoard(readToCharacter(parsedLine, idx));
		m.setID(stoi(readToCharacter(parsedLine, idx)));

		TreeNode* t = new TreeNode(m);
		board.insertInTree(t);
	}

	input.close();
	switch (tree) {
	case 1:
		board1 = board;
		break;
	case 2:
		board2 = board;
		break;
	case 3:
		board3 = board;
		break;
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

void Game::printBoard() {
	this->updateBoard();
	for (int i = 0; i < 3; i++) {
		cout << i << " ";
		for (int j = 0; j < 3; j++) {
			cout << "| " << this->curBoard[i][j] << " | ";
		}
		cout << endl << endl;
	}
	cout << "    0     1     2" << endl << endl;
}

void Game::updateBoard() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			this->curBoard[i][j] = '.';
		}
	}

	for (int i = 0; i < 3; i++) {
		this->curBoard[this->playerPawns[i].getRow()][this->playerPawns[i].getCol()] = 'p';
		this->curBoard[this->enemyPawns[i].getRow()][this->enemyPawns[i].getCol()] = 'e';
	}
}

void Game::printOptions() {
	if (this->legalPushes[0]) {
		cout << "Pawn 1 at " << this->playerPawns[0].getRow() << ", " << this->playerPawns[0].getCol() << endl;
	}
	if (this->legalPushes[1]) {
		cout << "Pawn 2 at " << this->playerPawns[1].getRow() << ", " << this->playerPawns[1].getCol() << endl;
	}
	if (this->legalPushes[2]) {
		cout << "Pawn 3 at " << this->playerPawns[2].getRow() << ", " << this->playerPawns[2].getCol() << endl;
	}
}