#include "Tile.hpp"
#include <Windows.h>

bool checkNeighbors(vector<int> neighbors, vector<Tile> tiles) {
	int paths = 0;
	for (int n : neighbors) {
		if (tiles[n - 1].checkPath()) {
			paths++;
		}
	}

	return paths == 1;
}

void addToList(vector<int> neighbors, vector<Tile> tiles, vector<int>& walls) {
	for (int n : neighbors) {
		if (!tiles[n - 1].checkPath()) {
			walls.push_back(n);
		}
	}
}

int main() {
	srand(time(NULL));
	int mazeWidth = 0;
	vector<Tile> tiles;
	vector<int> walls;

	do {
		cout << "Enter the size of the maze you want to make (enter an integer from 5-20, the maze will be of size nxn): ";
		cin >> mazeWidth;
	} while (mazeWidth < 5 || mazeWidth > 20);
	system("cls");

	for (int i = 0; i < mazeWidth * mazeWidth; i++) {
		Tile t(i + 1);
		t.setType(mazeWidth);
		tiles.push_back(t);
	}

	int idx = rand() % (mazeWidth * mazeWidth);
	tiles[idx].makePath();
	tiles[idx].addWalls(walls);

	while (walls.size() > 0) {
		int selection = rand() % walls.size();
		int wall = walls[selection] - 1;
		bool isTrail = checkNeighbors(tiles[wall].getNeighbors(), tiles);

		if (isTrail) {
			tiles[wall].makePath();
			addToList(tiles[wall].getNeighbors(), tiles, walls);
		}

		walls.erase(walls.begin() + selection);

		system("cls");
		for (int i = 0; i < mazeWidth; i++) {
			for (int j = 0; j < mazeWidth; j++) {
				if (!tiles[mazeWidth * i + j].checkPath()) {
					cout << "  ";
				}
				else {
					cout << "O ";
				}
			}
			cout << endl;
		}
	}

	return 0;
}