#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using std::cout;
using std::cin;
using std::vector;
using std::endl;

/*
	0 - LeftCornerTop		5 - RightEdge
	1 - RightCornerTop		6 - TopEdge
	2 - LeftCornerBot		7 - BotEdge
	3 - RightCornerBot		8 - CenterTile
	4 - LeftEdge
*/
class Tile {
public:
	Tile();
	Tile(int count);

	void setType(int mazeWidth);
	void addWalls(vector<int>& walls);
	bool checkPath() { return this->isPath; }
	bool checkVisit() { return this->visited; }
	bool isDead() { return this->dead; }
	int getID() { return this->ID; }
	vector<int> getNeighbors() { return this->neighbors; }
	void makePath() { this->isPath = true; }
	void logVisit() { this->visited = true; }
	void labelDead() { this->dead = true; }
private:
	bool isPath;
	bool visited;
	bool dead;
	int ID;
	vector<int> neighbors;
};