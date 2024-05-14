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

void Player::stockMenu(int idx) {
	int selection = 0;
	system("cls");
	cout << "Would you like to buy or sell " << this->stocks[idx].getName() << " stocks?" << endl;
	cout << "1. Buy" << endl;
	cout << "2. Sell" << endl;
	cin >> selection;
	if (selection == 1) {
		this->buyStock(idx);
	}
	else {
		this->sellStock(idx);
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

void Player::buyStock(int idx) {
	int selection = 0;
	bool bought = false;
	do {
		cout << "Current Money: " << std::setprecision(6) << this->money << endl;
		cout << "Enter the number of stocks you wish to buy. Max " << this->stocks[idx].getMaxInv() - this->stocks[idx].getCurInv() << endl;
		cin >> selection;
		if (selection < 0) { selection = 0; }
		else if (selection + this->stocks[idx].getCurInv() > this->stocks[idx].getMaxInv()) {
			selection = this->stocks[idx].getMaxInv() - this->stocks[idx].getCurInv();
		}

		if (selection * this->stocks[idx].getPrice() > this->money) {
			cout << "You can't afford this much stock!" << endl;
		}
		else {
			this->stocks[idx].addInv(selection);
			this->money -= selection * this->stocks[idx].getPrice();
			cout << "Bought " << selection << " stocks." << endl;
			cout << "Remaining Money: " << std::setprecision(6) << this->money << endl;
			bought = true;
		}
		system("pause");
	} while (!bought);
}

void Player::sellStock(int idx) {
	int selection = 0;
	bool sold = false;

	cout << "Current Money: " << std::setprecision(6) << this->money << endl;
	cout << "How many of your stocks would you like to sell? Max " << this->stocks[idx].getCurInv() << endl;
	cin >> selection;
	if (selection < 0) { selection = 0; }
	else if (selection > this->stocks[idx].getCurInv()) { selection = this->stocks[idx].getCurInv(); }

	this->stocks[idx].removeInv(selection);
	this->money += selection * this->stocks[idx].getPrice();
	cout << "Sold " << selection << " stocks." << endl;
	cout << "Total Money: " << std::setprecision(6) << this->money << endl;
	system("pause");
}