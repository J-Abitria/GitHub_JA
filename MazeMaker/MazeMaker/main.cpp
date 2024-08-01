#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::vector;
using std::endl;

int main() {
	int mazeWidth = 0;
	vector<bool> tiles;

	do {
		cout << "Enter the size of the maze you want to make (enter an integer from 3-15, the maze will be of size nxn): ";
		cin >> mazeWidth;
	} while (mazeWidth < 3 || mazeWidth > 15);
	system("cls");

	for (int i = 0; i < mazeWidth * mazeWidth; i++) {
		tiles.push_back(false);
	}

	for (int i = 0; i < mazeWidth; i++) {
		for (int j = 0; j < mazeWidth; j++) {
			if (!tiles[3 * i + j]) {
				cout << "X ";
			}
		}
		cout << endl;
	}

	return 0;
}