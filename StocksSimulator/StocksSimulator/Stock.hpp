#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::string;

class Stock {
public:
	Stock(string n, int m, double v) {
		this->name = n;
		this->maxInventory = m;
		this->volatility = v;
	}

	Stock(Stock& s) {
		this->name = s.name;
		this->maxInventory = s.maxInventory;
		this->volatility = s.volatility;
	}

	~Stock() {

	}


private:
	string name;
	int maxInventory;
	double volatility;
};