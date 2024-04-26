#pragma once
#include "Enemy.hpp"
#include "Player.hpp"


/*
	Class: Tower
	
	Description: This class represents the base values that all types of Towers share, with the positioning, size, and the target.
*/
class Tower {
public:
	// Assignment constructor for the Tower
	Tower(double x, double y) {
		this->damage = 1;
		this->hitbox.setSize(sf::Vector2f(50, 50));
		this->hitbox.setPosition(sf::Vector2f(x, y));
		this->target = new Enemy();
		this->type = -1;
	}

	// Targets the closest Enemy to the exit (which will always be at the front of the vector)
	void findTarget(std::vector<Enemy*> list) { this->target = list.front(); }

	// Pure virtual function - overriden in every derived Tower class.
	virtual void fire(std::vector<Enemy*>& list, Player& p) = 0;

	/*
		Function: placeTower
		
		Description: This function checks if the current positioning of the Tower is in the bounds of the game window, and if it overlaps the path.
		If not, true is returned, false otherwise.
		Precondition: Map, RenderWindow are properly initialized with values and states, x and y represent the tentative position of the Tower.
		Postcondition: The correct return value is reached.
	*/
	bool placeTower(Map m, sf::RenderWindow& w, double x, double y) {
		int index = 0;

		if (!m.intersectsPath(this->hitbox, index)) {
			if (0 <= x <= 950 && 0 <= y <= 950) {
				return true;
			}
		}
		return false;
	}

	// Getter method for Tower hitbox.
	sf::RectangleShape getHitbox() { return this->hitbox; }

	// Draws the current tower to the screen.
	void drawTower(sf::RenderWindow& w) {
		this->hitbox.setTexture(&this->t);
		w.draw(this->hitbox);
	}

	Enemy* getTarget() {
		return this->target;
	}

	int getDamage() {
		return this->damage;
	}

	int getType() {
		return this->type;
	}
protected:
	// Attributes for the Tower - set to protected so derived classes have direct access.
	sf::RectangleShape hitbox;
	sf::Texture t;
	int damage;
	Enemy* target;
	int type;
};