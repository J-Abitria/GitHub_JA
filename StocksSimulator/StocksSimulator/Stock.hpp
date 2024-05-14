#include <iostream>
#include <iomanip>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;
using std::string;

class Stock {
public:
	Stock() {
		this->name = "";
		this->maxInv = 0;
		this->curInv = 0;
		this->volatility = 0.0;
		this->price = 0.0;
	}

	Stock(string n, int m, double v, double avgP) {
		int variance = rand() % 1000 + 1, sign = rand() % 2;
		this->name = n;
		this->maxInv = m;
		this->curInv = 0;
		this->volatility = v;
		if (sign) {
			this->price = avgP + ((double)variance / 100);
		}
		else {
			this->price = avgP - ((double)variance / 100);
		}
	}

	Stock(Stock& s) {
		this->name = s.name;
		this->maxInv = s.maxInv;
		this->curInv = s.curInv;
		this->volatility = s.volatility;
		this->price = s.price;
	}

	~Stock() {

	}
	
	string getName() { return this->name; }
	int getCurInv() { return this->curInv; }
	int getMaxInv() { return this->maxInv; }
	double getPrice() { return this->price; }

	double updatePrice();
private:
	string name;
	int maxInv;
	int curInv;
	double volatility;
	double price;
};

std::ostream& operator<< (std::ostream& lhs, Stock rhs);