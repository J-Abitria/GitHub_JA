#pragma once
#include "Tower.hpp"

class LightningTower : public Tower {
public:
	LightningTower(double x, double y) : Tower(x, y) {
		this->t.loadFromFile("Lightning_Tower.png");
		this->damage = 1;
		this->type = 1;
		this->chain = 3;
	}

	void fire(std::vector<Enemy*>& list, Player& p) {
		int attacks = 0, i = 0;

		while ((attacks < this->chain && !list.empty()) && i < list.size()) {
			list.at(i)->hurt(this->damage);
			list.at(i)->tag();

			if (!this->target->isAlive()) {
				p.gainMana(list.at(i)->getLoot());
				list.erase(list.begin() + i);
			}
			else {
				i++;
			}
			attacks++;
		}
	}

private:
	int chain;
};