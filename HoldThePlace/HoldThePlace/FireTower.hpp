#pragma once
#include "Tower.hpp"

/*
	Class: FireTower (derived from Tower)

	Description: This class represents a Tower that attacks a single Enemy each second, dealing 1 damage.
*/
class FireTower : public Tower {
public:
	// Assignment constructor, loads the proper image for the Tower.
	FireTower(double x, double y) : Tower(x, y) {
		this->damage = 2;
		this->t.loadFromFile("Fire_Tower.png");
		this->type = 0;
	}

	// Default destructor.
	~FireTower() {

	}

	/*
		Function: fire

		Description: This function is overloaded from Tower's pure virtual function fire. This function calls findTarget to find the closest
		Enemy to the exit, then deals 1 damage to the Enemy, and tags it to denote that it has been hit. It also will erase the targeted Enemy
		from the vector if its HP is now 0.
		Precondition: The list of Enemies is not empty.
		Postcondition: The targeted Enemy took damage and is now tagged, the list may have 1 less Enemy.
	*/
	void fire(std::vector<Enemy*>& list, Player& p) {
		this->findTarget(list);
		this->target->hurt(this->damage);
		this->target->tag();
		// Checks if the Enemy still has health.
		if (!this->target->isAlive()) {
			p.gainMana(list.front()->getLoot());
			list.erase(list.begin());
		}
	}
};