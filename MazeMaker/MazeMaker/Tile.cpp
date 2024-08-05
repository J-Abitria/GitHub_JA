#include "Tile.hpp"

Tile::Tile() {
	this->isPath = false;
	this->visited = false;
	this->dead = false;
	this->ID = 0;
}

Tile::Tile(int count) {
	this->isPath = false;
	this->visited = false;
	this->dead = false;
	this->ID = count;
}

void Tile::setType(int mazeWidth) {
	if (this->ID != 1) {
		if (this->ID == mazeWidth) {
			this->neighbors.push_back(this->ID - 1);
			this->neighbors.push_back(this->ID + mazeWidth);
		}
		else if (this->ID == mazeWidth * mazeWidth - (mazeWidth - 1)) {
			this->neighbors.push_back(this->ID + 1);
			this->neighbors.push_back(this->ID - mazeWidth);
		}
		else if (this->ID == mazeWidth * mazeWidth) {
			this->neighbors.push_back(this->ID - 1);
			this->neighbors.push_back(this->ID - mazeWidth);
		}
		else {
			if (this->ID <= mazeWidth) {
				this->neighbors.push_back(this->ID + 1);
				this->neighbors.push_back(this->ID - 1);
				this->neighbors.push_back(this->ID + mazeWidth);
			}
			else if (this->ID > (mazeWidth - 1) * mazeWidth) {
				this->neighbors.push_back(this->ID + 1);
				this->neighbors.push_back(this->ID - 1);
				this->neighbors.push_back(this->ID - mazeWidth);
			}
			else if (this->ID % mazeWidth == 0) {
				this->neighbors.push_back(this->ID + mazeWidth);
				this->neighbors.push_back(this->ID - mazeWidth);
				this->neighbors.push_back(this->ID - 1);
			}
			else if (this->ID % mazeWidth == 1) {
				this->neighbors.push_back(this->ID + mazeWidth);
				this->neighbors.push_back(this->ID - mazeWidth);
				this->neighbors.push_back(this->ID + 1);
			}
			else {
				this->neighbors.push_back(this->ID + mazeWidth);
				this->neighbors.push_back(this->ID - mazeWidth);
				this->neighbors.push_back(this->ID + 1);
				this->neighbors.push_back(this->ID - 1);
			}
		}
	}
	else {
		this->neighbors.push_back(this->ID + 1);
		this->neighbors.push_back(this->ID + mazeWidth);
	}
}

void Tile::addWalls(vector<int>& walls) {
	for (int i : neighbors) {
		walls.push_back(i);
	}
}