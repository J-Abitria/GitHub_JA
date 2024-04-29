#pragma once


#include "Unit.hpp"
#include "Map.hpp"


/*
	Class: Enemy (derived from Unit)

	Description: this class represents the objects moving along the path in order to damage the player if they reach the end.
	The Enemies move constantly, and can be damaged/destroyed by Towers.
*/
class Enemy : public Unit
{
public:
	// Default constructor for default values.
	Enemy() : Unit(0) {
		this->speed = 0.0;
		this->damage = 0;
		this->loot = 0;
		this->movements = 0;
		this->currentTile = 0;
		this->hurtFrames = 0;
		this->tagged = false;
		this->t.loadFromFile("Voidling.png");
		this->hitbox.setTexture(this->t);
	}

	// Assignment constructor for the size, position, health, and damage of the enemy.
	Enemy(const sf::Vector2f& size, const sf::Vector2f& pos, int health, int d) : Unit(health)
	{
		// Attributes specific to the enemy.
		this->speed = 0.0;
		this->damage = d;
		this->loot = 1;
		this->movements = 0;
		this->currentTile = 0;
		this->hurtFrames = 0;
		this->tagged = false;
		// Attributes related to the object's rendering.
		this->hitbox.setPosition(pos);
		this->t.loadFromFile("Voidling.png");
		this->hitbox.setTexture(this->t);
		this->hitbox.setOrigin(25, 25);
	}

	// Default destructor
	~Enemy() {

	}

	// Getter methods for damage, movement, and the current Tile the Enemy is located on.
	int getDamage() { return this->damage; }

	int getMovements() { return this->movements; }

	int getTile() { return this->currentTile; }

	// Setter method to represent that the Enemy is now on the next Tile.
	void nextTile() {
		this->currentTile++;
	}

	/*
		Function: updateMove

		Description: This function determines the Direction that the Enemy should go, based on the internal information of the Tile's assigned
		direction to guide the Enemy. The function subsequently rotates the Sprite of the Enemy appropriately and calls the associated move
		function.
		Precondition: currentTile contains information about a direction.
		Postcondition: The Sprite has been rotated to the correct angle, and the correct move function is called based on newDirection.
	*/
	void updateMove(Tile currentTile) {
		// Gets the new Direction and logs the current movement.
		Direction newDirection = currentTile.getDirection();
		this->movements++;
		// Calls the appropriate move function based on the Direction.
		switch (newDirection) {
		case right:
			this->hitbox.setRotation(0);
			this->crawlright(0);
			break;
		case left:
			this->hitbox.setRotation(180);
			this->crawlleft(0);
			break;
		case up:
			this->hitbox.setRotation(270);
			this->crawlup(0);
			break;
		case down:
			this->hitbox.setRotation(90);
			this->crawldown(0);
			break;
		}
	}

	/*
		Function: drawEnemy

		Description: This function renders the current state of the Enemy to the window. If the Enemy has been attacked by a Tower, it will
		flash red for 10 frames before returning to its default state.
		Precondition: sf::RenderWindow w is currently open, the image of the Sprite is correctly rotated.
		Postcondition: The correct game state (hurt/not hurt) of the Enemy is displayed on screen.
	*/
	void drawEnemy(sf::RenderWindow& w) {
		sf::Texture hurt;
		hurt.loadFromFile("Voidling_Hit.png");
		// Flashes the Enemy red if attacked, logs the amount of frames it is displayed red.
		if (this->tagged) {
			this->hitbox.setTexture(hurt);
			this->hurtFrames++;
		}

		w.draw(this->hitbox);
		// Resets the display state to normal after 10 frames.
		if (this->hurtFrames == 10) {
			this->hitbox.setTexture(this->t);
			this->tagged = false;
			this->hurtFrames = 0;
		}
	}

	sf::Sprite getHitbox() { return this->hitbox; }

	int getLoot() { return this->loot; }

	// Denotes an attacked Enemy.
	void tag() { this->tagged = true; }
private:
	/*
		Functions: crawlup, crawldown, crawlright, crawlleft

		Description: These functions move the Enemy's Sprite by the given speed. sped denotes the offset of the object by pixels. As a note,
		a negative y value moves the Enemy up.
		Postcondition: The Enemy was moved the correct direction by sped's value.
	*/
	void crawlup(int slow) {
		double sped = 2;
		if (slow == 1) {
			sped = speed / 2;
		}
		this->hitbox.move(0, -sped);
	}
	void crawldown(int slow) {
		double sped = 2;
		if (slow == 1) {
			sped = speed / 2;
		}
		this->hitbox.move(0, sped);
	}
	void crawlright(int slow) {
		double sped = 2;
		if (slow == 1) {
			sped = speed / 2;
		}
		this->hitbox.move(sped, 0);
	}
	void crawlleft(int slow) {
		double sped = 2;
		if (slow == 1) {
			sped = speed / 2;
		}
		this->hitbox.move(-sped, 0);
	}
	// Private attributes
	double speed;
	int damage;
	int loot; // Not currently in use.
	int movements;
	int currentTile;
	int hurtFrames;
	bool tagged;
	sf::Sprite hitbox;
	sf::Texture t;
};