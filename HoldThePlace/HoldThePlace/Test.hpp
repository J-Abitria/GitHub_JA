#pragma once

#include <SFML/Graphics.hpp>

#include "FireTower.hpp"
#include "LightningTower.hpp"
#include "Projectile.hpp"
#include <fstream>
#include <string>

class Test {
public:
	Test() {

	}

	~Test() {

	}

	void runTests() {
		this->testLose();
		this->testWin();
		this->testEnemyKill();
		this->testTowerCost();
		this->testTowerType();
	}
private:
	void testLose() {
		Player testP;
		sf::RenderWindow test(sf::VideoMode(100, 100), "Testing");

		testP.setHealth(0);
		if (!testP.checkLose(test)) {
			throw std::invalid_argument("Loss condition gave an unexpected return value.");
		}
	}

	void testWin() {
		Player testP;
		sf::RenderWindow test(sf::VideoMode(100, 100), "Testing");
		std::vector<Wave*> testWave;

		if (!testP.checkWin(test, testWave)) {
			throw std::invalid_argument("Win condition gave an unexpected return value.");
		}
	}

	void testEnemyKill() {
		Player testP;
		std::vector<Enemy*> testUnits;
		FireTower testFire(0, 0);
		testUnits.push_back(new Enemy(sf::Vector2f(50, 50), sf::Vector2f(0, 0), 1, 0));

		testFire.fire(testUnits, testP);

		if (!testUnits.empty()) {
			throw std::invalid_argument("Enemy was not successfully removed from vector.");
		}
	}

	void testTowerCost() {
		Player testP;

		testP.towerCost();

		if (testP.getMana() > 0) {
			throw std::invalid_argument("Player information not successfully updated.");
		}
	}

	void testTowerType() {
		Tower* testTower = new LightningTower(0, 0);

		if (testTower->getType() != 1) {
			throw std::invalid_argument("Incorrect tower initialization.");
		}
	}
};