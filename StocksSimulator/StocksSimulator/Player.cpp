#include "Player.hpp"

void Player::populateStocks() { this->populateStocksPriv(); }

void Player::printStocks() {
	system("cls");
	for (int i = 0; i < 7; i++) {
		cout << this->stocks[i];
		cout << " (" << this->percentages[i] / 100 << "%)" << endl;
	}
}

void Player::updateStocks() {
	for (int i = 0; i < 7; i++) {
		this->percentages[i] = this->stocks[i].updatePrice();
	}
}

void Player::populateStocksPriv() {
	string names[7] = { "1", "2", "3", "4", "5", "6", "7" };
	int maxes[7] = { 100, 100, 150, 225, 50, 75, 125 };
	double volatilities[7] = { 1000, 400, 1500, 1800, 2400, 300, 800 };
	double avgPrices[7] = { 30.0, 60.0, 25.0, 15.0, 75.0, 70.0, 45.0 };

	for (int i = 0; i < 7; i++) {
		this->stocks[i] = Stock(names[i], maxes[i], volatilities[i], avgPrices[i]);
	}
}