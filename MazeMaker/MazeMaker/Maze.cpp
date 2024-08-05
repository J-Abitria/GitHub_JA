#include "Maze.hpp"

Maze::Maze() {
	this->start = -1;
	this->end = -1;
	this->mazeWidth = 0;
}

int Maze::checkNeighbors(vector<int> neighbors) {
	int paths = 0;

	for (int n : neighbors) {
		if (this->tiles[n - 1].checkPath()) {
			paths++;
		}
	}

	return paths;
}

void Maze::addToList(vector<int> neighbors) {
	for (int n : neighbors) {
		if (!tiles[n - 1].checkPath()) {
			this->walls.push_back(n);
		}
	}
}

void Maze::printMaze() {
	system("cls");
	for (int i = 0; i < this->mazeWidth; i++) {
		for (int j = 0; j < this->mazeWidth; j++) {
			if (this->tiles[this->mazeWidth * i + j].checkVisit()) {
				if (this->tiles[this->mazeWidth * i + j].isDead()) {
					cout << "X ";
				}
				else {
					cout << "V ";
				}
			}
			else if (!this->tiles[this->mazeWidth * i + j].checkPath()) {
				cout << "  ";
			}
			else {
				if (this->start == this->tiles[this->mazeWidth * i + j].getID()) {
					cout << "S ";
				}
				else if (this->end == this->tiles[this->mazeWidth * i + j].getID()) {
					cout << "E ";
				}
				else {
					cout << "O ";
				}
			}
		}
		cout << endl;
	}
}

void Maze::makeMaze() {
	srand(time(NULL));

	do {
		cout << "Enter the size of the maze you want to make (enter an integer from 5-20, the maze will be of size nxn): ";
		cin >> this->mazeWidth;
	} while (this->mazeWidth < 5 || this->mazeWidth > 20);

	for (int i = 0; i < this->mazeWidth * this->mazeWidth; i++) {
		Tile t(i + 1);
		t.setType(this->mazeWidth);
		this->tiles.push_back(t);
	}

	int idx = rand() % (this->mazeWidth * this->mazeWidth);
	this->tiles[idx].makePath();
	this->tiles[idx].addWalls(walls);
	if (this->tiles[idx].getNeighbors().size() != 4) {
		this->edges.push_back(this->tiles[idx]);
	}

	while (this->walls.size() > 0) {
		int selection = rand() % walls.size();
		int wall = this->walls[selection] - 1;
		int trails = this->checkNeighbors(this->tiles[wall].getNeighbors());

		if (trails == 1) {
			this->tiles[wall].makePath();
			this->addToList(this->tiles[wall].getNeighbors());
			if (this->tiles[wall].getNeighbors().size() != 4) {
				this->edges.push_back(this->tiles[wall]);
			}
		}

		this->walls.erase(walls.begin() + selection);

		this->printMaze();
	}
	
	while (this->start == -1 || this->end == -1) {
		int edge = rand() % edges.size();
		if (edges[edge].checkPath() && this->checkNeighbors(edges[edge].getNeighbors()) == 1) {
			if (this->start == -1) { this->start = edges[edge].getID(); }
			else if (this->start != edges[edge].getID()) { 
				this->end = edges[edge].getID(); 
				edges.clear();
			}
		}
	}

	// add print here
	this->printMaze();
	system("pause");
}

void Maze::solveMaze() {
	this->tiles[this->start - 1].logVisit();
	Stack moves(new Node(this->tiles[this->start - 1]));
	vector<Tile> possibleTrails;

	while (moves.peek()->getTile().getID() != this->end) {
		for (int n : moves.peek()->getTile().getNeighbors()) {
			if (this->tiles[n - 1].checkPath() && !this->tiles[n - 1].checkVisit()) {
				possibleTrails.push_back(this->tiles[n - 1]);
			}
		}
		if (possibleTrails.size() > 1) {
			int selection = rand() % possibleTrails.size();
			this->tiles[possibleTrails[selection].getID() - 1].logVisit();
			moves.push(new Node(possibleTrails[selection]));
		}
		else if (possibleTrails.size() == 1) {
			this->tiles[possibleTrails[0].getID() - 1].logVisit();
			moves.push(new Node(possibleTrails[0]));
		}
		else {
			do {
				this->tiles[moves.peek()->getTile().getID() - 1].labelDead();
				moves.pop();
			} while (moves.peek()->getTile().getNeighbors().size() == 1);
		}
		possibleTrails.clear();
		this->printMaze();
	}
}