#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

class Menu {
private:
	void playGame() {
		srand(time(NULL));
		bool hasWon = false;
		const char colors[5] = { 'Y', 'R', 'B', 'G', 'O' };
		int frequency[5] = { 0 };
		int correctColors = 0;

		for (int i = 0; i < 5; i++) {
			int idx = -1;

			do {
				idx = rand() % 5;
			} while (frequency[idx]);

			frequency[idx]++;
			this->order[i] = colors[idx];
		}

		do {
			if (guesses == 0) {
				cout << "The colors Yellow, Red, Blue, Green, and Orange have been randomly shuffed. Enter the first letter of each color, separated " <<
					"by a space to guess the order of the colors (ex. Y B G O R)." << endl;
			}
			else { cout << "You guessed " << correctColors << " correct colors." << endl; }
			cin >> this->input[0] >> this->input[1] >> this->input[2] >> this->input[3] >> this->input[4];

			correctColors = 0;
			for (int i = 0; i < 5; i++) {
				if (this->input[i] == this->order[i]) {
					correctColors++;
				}
			}

			this->guesses++;
			if (correctColors == 5) { hasWon = true; }
		} while (!hasWon);

		cout << "You won in " << this->guesses << " guesses!";
	}

	char* order;
	char* input;
	int guesses;
public:
	Menu() {
		this->order = new char[5];
		this->input = new char[5];
		this->guesses = 0;
	}

	void showMenu() {
		cout << "Welcome to 5 Color Match!" << endl;
		cout << "The computer will assign 5 colors in a random order. The game will prompt you to enter the first letter of each color to guess the order " <<
			"of the colors. It will then tell you how many colors are placed in the correct position, but not which ones. The goal is to enter all 5 colors in the " <<
			"correct order in the fewest amount of guesses. Press any key to begin!" << endl;
		system("pause");
		system("cls");
		playGame();
	}
};