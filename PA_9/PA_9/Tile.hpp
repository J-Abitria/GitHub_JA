#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

// Enumerated type for the Direction of each Tile, allows for more readability.
enum Direction {
	right = 0, left = 180, up = 270, down = 90, none = -1
};

/*
	Class: Tile
	
	Description: This class represents a single Tile, of 50x50 pixels in size, that denotes a path that the Enemy moves upon.
*/
class Tile {
public:
	// Default constructor
	Tile() { this->dir = none; }

	// Getter method to find the internal direction of the Tile.
	Direction getDirection() { return this->dir; }

	// Setter methods
	void setRectangle(double x, double y) { this->rect.setSize(sf::Vector2f(x, y)); }

	void setSpot(double x, double y) { this->rect.setPosition(x, y); }

	void setDirection(Direction newDirection) { this->dir = newDirection; }

	// Checks if the hitbox of the tower collides with the Tile at any point.
	bool isColliding(sf::RectangleShape tower) { return this->rect.getGlobalBounds().intersects(tower.getGlobalBounds()); }

private:
	// Attributes for Tile information and image rendering.
	sf::RectangleShape rect;
	sf::Texture image;
	Direction dir;
};
