#include "Game.hpp"

Game::Game() {
	for (int i = 0; i < 3; i++) {
		Pawn p(2, i);
		Pawn e(0, i);
		this->playerPawns[i] = p;
	}

	for (int i = 0; i < 6; i++) {
		if (i < 3) {
			this->legalPushes[i] = true;
			this->curBoard[0][i] = 'e';
		}
		else {
			this->curBoard[1][i % 3] = '.';
		}
		this->legalCaptures[i] = false;
	}
}

void Game::playGame() {
	int pawnMove = 0;
	bool playerWin = false, cpuWin = false;
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
			this->currentPosition = board1.getHead();
			break;
		case 2:
			if (board2.getHead() == nullptr)
				this->populateTree(2);
			this->currentPosition = board2.getHead();
			break;
		case 3:
			if (board3.getHead() == nullptr)
				this->populateTree(3);
			this->currentPosition = board3.getHead();
			break;
		}
	}
	do {
		this->makeComputerMove();
		cpuWin = this->checkCpuWin();
		if (!cpuWin) {
			cout << "New board: " << this->currentPosition->getData().getBoard() << " - " << this->currentPosition->getData().getID() << endl;
			this->printBoard();
			cout << "Enter the number of the pawn you wish to move (1-3):" << endl;
			this->printOptions();
			do {
				cin >> pawnMove;
			} while (pawnMove < 0 || pawnMove > 4);
			this->moveOptions(pawnMove - 1);
			this->travelTree();
			playerWin = this->checkPlayerWin();
		}
	} while (!playerWin && !cpuWin);

	this->printBoard();
	if (playerWin) { cout << "You win!" << endl; }
	if (cpuWin) { cout << "Computer wins!" << endl; }
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
			if (this->curBoard[i][j] == 'p') {
				this->curBoard[i][j] = '.';
			}
		}
	}

	for (int i = 0; i < 3; i++) {
		if (this->curBoard[this->playerPawns[i].getRow()][this->playerPawns[i].getCol()] != 'e' && !this->playerPawns[i].isCaptured()) {
			this->curBoard[this->playerPawns[i].getRow()][this->playerPawns[i].getCol()] = 'p';
		}
		else {
			this->playerPawns[i].capture();
		}
	}
}

void Game::printOptions() {
	if (!this->playerPawns[0].isCaptured() && (this->checkPush(0) || this->checkLeft(0) || this->checkRight(0))) {
		cout << "Pawn 1 at " << this->playerPawns[0].getRow() << ", " << this->playerPawns[0].getCol() << endl;
	}
	if (!this->playerPawns[1].isCaptured() && (this->checkPush(1) || this->checkLeft(1) || this->checkRight(1))) {
		cout << "Pawn 2 at " << this->playerPawns[1].getRow() << ", " << this->playerPawns[1].getCol() << endl;
	}
	if (!this->playerPawns[2].isCaptured() && (this->checkPush(2) || this->checkLeft(2) || this->checkRight(2))) {
		cout << "Pawn 3 at " << this->playerPawns[2].getRow() << ", " << this->playerPawns[2].getCol() << endl;
	}
}

void Game::travelTree() {
	string boardData = "";

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			boardData += this->curBoard[i][j];
		}
		if (i < 2)
			boardData += '/';
	}
	vector<TreeNode*> options = this->currentPosition->getChildren();

	for (int i = 0; i < options.size(); i++) {
		if (options[i]->getData().getBoard() == boardData) {
			this->currentPosition = options[i];
		}
	}
}

void Game::makeComputerMove() {
	int row = 0, col = 0;
	int positions = this->currentPosition->getChildren().size(),
		choice = rand() % positions;

	this->currentPosition = this->currentPosition->getChildren()[choice];

	cout << "New board: " << this->currentPosition->getData().getBoard() << " - " << this->currentPosition->getData().getID();
	for (int i = 0; i < 11; i++) {
		if (this->currentPosition->getData().getBoard()[i] != '/') {
			this->curBoard[row][col] = this->currentPosition->getData().getBoard()[i];
			col++;
			if (col == 3) {
				row++;
				col = 0;
			}
		}
	}
}

bool Game::checkPush(int pawn) {
	int row = this->playerPawns[pawn].getRow(), col = this->playerPawns[pawn].getCol();

	return (row - 1 > -1) && (this->curBoard[row - 1][col] == '.');
}

bool Game::checkLeft(int pawn) {
	int row = this->playerPawns[pawn].getRow(), col = this->playerPawns[pawn].getCol();

	return (row - 1 > -1 && col - 1 > -1) && (this->curBoard[row - 1][col - 1] == 'e');
}

bool Game::checkRight(int pawn) {
	int row = this->playerPawns[pawn].getRow(), col = this->playerPawns[pawn].getCol();

	return (row - 1 > -1 && col + 1 < 3) && (this->curBoard[row - 1][col + 1] == 'e');
}

void Game::moveOptions(int pawn) {
	bool pushable = this->checkPush(pawn), leftable = this->checkLeft(pawn), rightable = this->checkRight(pawn);
	bool played = false;
	int option = 0;

	if (pushable && !(leftable || rightable)) {
		this->playerPawns[pawn].pushPawn();
	}
	else if (leftable && !(rightable || pushable)) {
		this->playerPawns[pawn].captureLeft();
	}
	else if (rightable && !(leftable || pushable)) {
		this->playerPawns[pawn].captureRight();
	}
	else {
		if (pushable) { cout << "| Push the pawn (1) | "; }
		if (leftable) { cout << "| Capture left (2) | "; }
		if (rightable) { cout << "| Capture right (3) |"; }
		cout << endl;
		do {
			cout << "Enter one of the valid options on screen:" << endl;
			cin >> option;
			this->curBoard[this->playerPawns[pawn].getRow()][this->playerPawns[pawn].getCol()] = '.';
			if (option == 1 && pushable) { 
				this->playerPawns[pawn].pushPawn(); 
				played = true;
			}
			else if (option == 2 && leftable) {
				this->playerPawns[pawn].captureLeft();
				played = true;
			}
			else if (option == 3 && rightable) {
				this->playerPawns[pawn].captureRight();
				played = true;
			}
		} while (!played);
	}
	this->curBoard[this->playerPawns[pawn].getRow()][this->playerPawns[pawn].getCol()] = 'p';
}

bool Game::checkPlayerWin() {
	int pawns = 0;

	for (int i = 0; i < 3; i++) {
		if (this->playerPawns[i].getRow() == 0) { return true; }
		for (int j = 0; j < 3; j++) {
			if (this->curBoard[i][j] == 'e') { pawns++; }
		}
	}

	if (pawns == 0) { return true; }

	return this->currentPosition->getChildren().empty();
}

bool Game::checkCpuWin() {
	int pawns = 0;

	for (int i = 0; i < 3; i++) {
		if (this->curBoard[2][i] == 'e') {
			return true;
		}
		for (int j = 0; j < 3; j++) {
			if (this->curBoard[i][j] == 'p') { pawns++; }
		}
	}

	if (pawns == 0) { return true; }

	return this->currentPosition->getChildren().empty();
}