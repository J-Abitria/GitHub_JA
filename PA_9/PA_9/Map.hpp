#pragma once
#include "Tile.hpp"

/*
	Class: Map
	
	Description: This class represents the Tiles that represent the path that the Enemies travel upon.
*/
class Map {
public:
	// Default constructor - builds the array of Tiles one by one, and assigns the appropriate Direction to them
	Map() {
		// Sets the spawning Tile's positioning, and ensures that spawned Enemies will start moving right. Each Tile is 50x50.
		this->map[0].setSpot(0, 700);
		this->map[0].setDirection(right);
		int i = 1;
		// Continues setting the adjacent tiles to the same Direction
		for (; i < 15; i++) {
			this->map[i].setSpot(i * 50, 700);
			this->map[i].setDirection(right);
		}
		// Denotes a corner that requires a different Direction to make the Enemies turn (ex. right right up)
		this->map[14].setDirection(up);
		// This pattern repeats until the path is laid out.
		for (; i < 18; i++) {
			this->map[i].setSpot(700, 700 - ((i - 14) * 50));
			this->map[i].setDirection(up);
		}
		this->map[17].setDirection(left);
		for (; i < 28; i++) {
			this->map[i].setSpot(700 - ((i - 17) * 50), 550);
			this->map[i].setDirection(left);
		}
		this->map[27].setDirection(up);
		for (; i < 35; i++) {
			this->map[i].setSpot(200, 550 - ((i - 27) * 50));
			this->map[i].setDirection(up);
		}
		this->map[34].setDirection(right);
		for (; i < 41; i++) {
			this->map[i].setSpot(200 + ((i - 34) * 50), 200);
			this->map[i].setDirection(right);
		}
		this->map[40].setDirection(down);
		for (; i < 46; i++) {
			this->map[i].setSpot(500, 200 + ((i - 40) * 50));
			this->map[i].setDirection(down);
		}
		this->map[45].setDirection(right);
		for (; i < 54; i++) {
			this->map[i].setSpot(500 + ((i - 45) * 50), 450);
			this->map[i].setDirection(right);
		}
		this->map[53].setDirection(up);
		for (; i < 62; i++) {
			this->map[i].setSpot(900, 450 - ((i - 53) * 50));
			this->map[i].setDirection(up);
		}
		// Establishes the despawn Tile.
		this->map[62].setSpot(900, 0);
		this->map[i].setDirection(none);
		// Sets the size of each Tile properly.
		for (int j = 0; j < 63; j++) {
			this->map[j].setRectangle(50, 50);
		}
	}

	// Getter method to get a Tile based on the integer passed in.
	Tile getSpecificTile(int current) { return this->map[current]; }

	/*
		Function: intersectsPath
		
		Description: This function determines if the given hitbox of the Tower intersects any Tile, and returns true. The function calls itself
		again with the next index, and repeats until true is returned, or the end of the array is reached.
		Precondition: tower is initialized, index is < 64
		Postcondition: The proper return value is reached.
	*/
	bool intersectsPath(sf::RectangleShape tower, int& index) {
		if (index == 63) {
			return false;
		}
		// Checks for Tile collision
		if (!map[index].isColliding(tower)) {
			index++;
			return intersectsPath(tower, index);
		}
		else {
			return true;
		}
	}
private:
	// Attribute for the path
	Tile map[63];
};
