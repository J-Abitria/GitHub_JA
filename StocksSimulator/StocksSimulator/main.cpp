/*
	Created by: James Abitria
	Project Name: Stocks Simulator
	Date Created: 5-13-24
	Last Update: 5-13-24
	
	Description: This program runs a "game" where the user can choose to buy or sell stocks based on their current values. Certain stocks
	have more volatility than others, and can be bought in higher or lower amounts.
*/
#include "Player.hpp"
#include <SFML/Graphics.hpp>

int main() {
	bool isRunning = true;
	int count = 0;
	Player p(1000.0);
	p.populateStocks();
	p.printStocks();
	srand(time(NULL));

	while (isRunning) {
		sf::Window w;
		w.setFramerateLimit(60);
		count++;
		if (count % 300 == 0) {
			p.updateStocks();
			p.printStocks();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			isRunning = false;
		}
	}

	return 0;
}