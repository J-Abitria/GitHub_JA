/*
	Created by: James Abitria
	Project Name: Stocks Simulator
	Date Created: 5-13-24
	Last Update: 5-13-24
	
	Description: This program runs a "game" where the user can choose to buy or sell stocks based on their current values. Certain stocks
	have more volatility than others, and can be bought in higher or lower amounts.
*/
#include <iostream>
#include <SFML/Graphics.hpp>

using std::cout;
using std::cin;
using std::endl;

int main() {
	bool isRunning = true;
	int count = 0;

	while (isRunning) {
		sf::Window w;
		w.setFramerateLimit(60);
		count++;
		cout << count << endl;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
			isRunning = false;
		}

	}

	return 0;
}