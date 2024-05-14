#include "Stock.hpp"

class Player {
public:
	Player(double m) {
		this->money = m;
		for (int i = 0; i < 7; i++) {
			percentages[i] = 0.0;
		}
	}

	~Player() {

	}

	void populateStocks();
	void printStocks();
	void updateStocks();
private:
	void populateStocksPriv();
	double money;
	Stock stocks[7];
	double percentages[7];
};