#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

/*
	Class: Wave
	
	Description: This function represents a single sequence of spawning a given amount of enemies of specific HP and potency.
*/
class Wave {
public:
	// Default constructor
	Wave() {
		this->numEnemies = 0;
		this->enemyHP = 0;
		this->spacing = 0;
	}

	// Default destructor
	~Wave() {

	}

	// Getter methods
	int getNumEnemies() const { return this->numEnemies; }

	int getEnemyHP() const { return this->enemyHP; }

	int getSpacing() const { return this->spacing; }

	// Setter methods
	void setNumEnemies(int enemies) { this->numEnemies = enemies; }

	void setHP(int HP) { this->enemyHP = HP; }

	void setSpacing(int spacing) { this->spacing = spacing; }
private:
	// Attributes for Wave information
	int numEnemies;
	int enemyHP;
	int spacing;
};