#pragma once
#include <vector>
#include "Wave.hpp"


/*
	Class: Player (derived from Unit)

	Description: This function represents the user, and their related health value as the game is played.
*/
class Player : public Unit {
public:
	// Default constructor (sets Player's HP to 20)
	Player() : Unit(20) {
		this->mana = 10;
		printInfo();
	}

	// Default destructor
	~Player() {

	}

	// Overriden version of the hurt function in Unit, allows for loss condition to be checked.
	void hurt(int damage, sf::RenderWindow& w) {
		this->health -= damage;
		if (this->health < 0) {
			this->health = 0;
		}
		printInfo();
		checkLose(w);
	}

	// Determines if the player has lost, closes the window and returns true if the loss condition is met, false otherwise
	bool checkLose(sf::RenderWindow& w) {
		if (!isAlive()) {
			std::cout << "You lose! Imagine failing to hold something." << std::endl;
			w.close();
			return true;
		}
		return false;
	}

	// Determines if the player has won if the vector of Enemies is empty, and all Enemies have been spawned, closing the window and
	// returning true if those conditions are met, false otherwise.
	bool checkWin(sf::RenderWindow& w, std::vector<Wave*> waves) {
		if (waves.size() == 0 && this->isAlive()) {
			std::cout << "You held the place!" << std::endl;
			w.close();
			return true;
		}
		return false;
	}

	bool checkEndWave(std::vector<Enemy*> units, int& spawns, int wave) {
		if (spawns == wave && units.size() == 0) {
			spawns = 0;
			return true;
		}
		return false;
	}

	int getMana() {
		return this->mana;
	}

	void towerCost() {
		this->mana -= 10;
		printInfo();
	}

	void gainMana(int amount) {
		this->mana += amount;
		printInfo();
	}

private:
	void printInfo() {
		system("cls");
		std::cout << "Health: " << this->health << std::endl;
		std::cout << "Mana: " << this->mana << std::endl;
	}
	int mana;
};