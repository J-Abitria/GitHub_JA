#include "Stock.hpp"

double Stock::updatePrice() {
	double percentage = rand() % ((int)volatility * 2) - (volatility * .9);

	this->price += price * (percentage / 10000);
	return percentage;
}

std::ostream& operator<< (std::ostream& lhs, Stock rhs) {
	lhs << rhs.getName() << " (" << rhs.getCurInv() << "/" << rhs.getMaxInv() << ") - ";
	if (rhs.getPrice() < 10) {
		cout << std::setprecision(3) << rhs.getPrice();
	}
	else {
		cout << std::setprecision(4) << rhs.getPrice();
	}

	return lhs;
}