#pragma once
#include "Stack.hpp"

class Maze {
public:
	Maze();
	void makeMaze();
	void solveMaze();
private:
	int checkNeighbors(vector<int> neighbors);
	void addToList(vector<int> neighbors);
	void printMaze();

	vector<Tile> tiles;
	vector<Tile> edges;
	vector<int> walls;
	int mazeWidth;
	int start;
	int end;
};