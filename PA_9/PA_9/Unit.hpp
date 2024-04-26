#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

/*
	Class: Unit
	
	Description: This class represents a base object in the game that has health and can be damaged.
*/
class Unit {
public:
	// Default constructor
	Unit() {
		this->health = 0;
	}

	// Assignment constructor to set a specific health.
	Unit(int h) {
		this->health = h;
	}

	// Default destructor
	~Unit() {

	}

	// Checks if the given Unit is alive.
	bool isAlive() { return this->health > 0; }

	// Damages the Unit by the amount passed in.
	void hurt(int amount) {
		if (this->health - amount <= 0) {
			this->health = 0;
		}
		else {
			this->health -= amount;
		}
	}

	// Getter method
	int getHealth() { return this->health; }

	void setHealth(int newHealth) { this->health = newHealth; }
protected:
	// Attribute for health - protected to allow for direct access by derived classes.
	int health;
};