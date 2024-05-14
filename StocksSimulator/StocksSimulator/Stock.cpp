#include "Stock.hpp"

double Stock::updatePrice() {
	double percentage = rand() % ((int)volatility * 2) - volatility;

	this->price += price * (percentage / 10000);
	return percentage;
}

std::ostream& operator<< (std::ostream& lhs, Stock rhs) {
	lhs << rhs.getName() << " (" << rhs.getCurInv() << "/" << rhs.getMaxInv() << ") - " << std::setprecision(4) << rhs.getPrice();

	return lhs;
}