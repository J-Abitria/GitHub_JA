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
	Tile(int count) {
		this->isPath = false;
		this->ID = count;
	}

	void setType(int mazeWidth) {
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

	void addWalls(vector<int>& walls) {
		for (int i : neighbors) {
			walls.push_back(i);
		}
	}

	bool checkPath() { return this->isPath; }
	int getID() { return this->ID; }
	vector<int> getNeighbors() { return this->neighbors; }
	void makePath() { this->isPath = true; }
private:
	bool isPath;
	int ID;
	vector<int> neighbors;
};