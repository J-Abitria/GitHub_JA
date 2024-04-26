#pragma once

#include <SFML/Graphics.hpp>

#include "FireTower.hpp"
#include "LightningTower.hpp"
#include "Projectile.hpp"
#include <fstream>
#include <string>


/*
	Class: Game
	
	Description: This class represents all of Hold the Place's operations. At runtime, an object of the game is made, and the game runs
	through this class.
*/
class Game
{
public:
	// Default constructor to initialize the game.
	Game() {

	}

	// Default destructor
	~Game() {

	}

	/*
		Function: runGame
		
		Description: This function is the heart of the gameplay loop for Hold the Place. It initializes the window where gameplay occurs, as well
		as tracking game events and updating the state of the game each frame.
	*/
	void runGame() {
		// Sets up the game window, the Map of path Tiles, and the Player's information
		sf::RenderWindow window(sf::VideoMode(1000, 1000), "Hold The Place");
		Map m;
		Player p;
		// Limits the framerate to 60 fps to ensure stable gameplay (when the framerate was unlimited sometimes the Enemies would accelerate
		// suddenly)
		window.setFramerateLimit(60);
		loadMap();
		int frame = 0, units = 0;
		this->readWaves();
		int waves = this->listWaves.size();
		// The gameplay while the window is opened.
		while (window.isOpen()) {
			// Tracks any and every event that occurs.
			sf::Event event;
			// This loop waits for any sort of user interaction. Any code inside the while loop only executes if an Event occurs (mouse move,
			// button press)
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
				}
				// Places a Tower upon left-click
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					if (p.getMana() >= 10) {
						if (this->addTower(m, window, sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, 0)) {
							p.towerCost();
						}
					}
				}

				if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
					if (p.getMana() >= 10) {
						if (this->addTower(m, window, sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, 1)) {
							p.towerCost();
						}
					}
				}
			}
			// Spawns a unit every half-second (CHANGE THIS TO SPACING FROM WAVE CLASS LATER)
			if (!this->listWaves.empty()) {
				if (frame % this->listWaves.at(0)->getSpacing() == 0 && units < this->listWaves.at(0)->getNumEnemies()) {
					this->addUnit();
					units++;
				}
			}
			// Executes the firing mechanic of every Tower. Regardless of when placed, each Tower fires every second.
			if (frame % 60 == 0 && !this->listUnits.empty()) {
				for (int i = 0; i < this->listTowers.size(); i++) {
					if (!this->listUnits.empty()) {
						this->listTowers.at(i)->findTarget(this->listUnits);
						Projectile* proj = new Projectile(sf::Vector2f(this->listTowers.at(i)->getHitbox().getPosition().x + 25, this->listTowers.at(i)->getHitbox().getPosition().y + 25), this->listTowers.at(i)->getDamage(), i, this->listTowers.at(i)->getType());
						proj->setTarget(this->listTowers.at(i)->getTarget());
						this->listProjectiles.push_back(proj);
					}
				}
			}

			if (!this->listProjectiles.empty()) {
				for (int i = 0; i < this->listProjectiles.size(); i++) {
					this->listProjectiles.at(i)->updatePosition();
					if (this->listProjectiles.at(i)->getBullet().getGlobalBounds().intersects(this->listProjectiles.at(i)->getTarget()->getHitbox().getGlobalBounds())) {
						if (!this->listUnits.empty()) {
							this->listTowers.at(this->listProjectiles.at(i)->getOrigin())->fire(this->listUnits, p);
						}
						this->listProjectiles.erase(this->listProjectiles.begin() + i);
					}
				}
				// Checks if all Enemies were eliminated by the last round of Tower attacks.
				if (p.checkEndWave(this->listUnits, units, this->listWaves.at(0)->getNumEnemies())) {
					if (this->listWaves.size() == 1) {
						this->listWaves.clear();
					}
					else {
						this->listWaves.erase(this->listWaves.begin());
					}
					p.checkWin(window, this->listWaves);
				}
			}
			// Runs game updates and renders the game state every frame, denoting the end of a single frame.
			updateGame(m, p, window, units);
			drawGame(window, p);
			frame++;
		}
	}

private:
	// Renders the map to the screen, this occurs before the gameplay loop to save time on rerendering the whole map every frame.
	void loadMap()
	{
		this->image.loadFromFile("Map_Background.png");
		this->background.setTexture(this->image);
	}

	// Calls updateUnit to track the movement and status of all Enemies. (Maybe move some operations from runGame into here?)
	void updateGame(Map m, Player& p, sf::RenderWindow& w, int& units)
	{
		updateUnit(m, p, w, units);
	}

	/*
		Function: updateUnit
		
		Description: This function updates the movement of all the Enemies on screen. It runs through the Enemy vector, and checks if the
		Enemy needs to move a different direction, should be despawned, or should continue moving as normal.
		Precondition: The Map, Player, RenderWindow, and units are all initialized with appropriate values and states.
		Postcondition: All Enemies in the vector have been properly updated, or the game will now conclude with a loss or win depending on if
		all Enemies have been despawned and if the Player has any HP remaining.
	*/
	void updateUnit(Map m, Player& p, sf::RenderWindow& w, int& units)
	{
		// Iterates through the whole Enemy vector.
		for (int i = 0; i < this->listUnits.size(); i++) 
		{
			// Checks if the Enemy has moved to the next Tile (each Tile is 50x50, so 25 movements of 2 pixels will put the Enemy on the next Tile)
			if (this->listUnits.at(i)->getMovements() > 0 && this->listUnits.at(i)->getMovements() % 25 == 0) {
				// Logs this change if the Enemy is on the next Tile.
				this->listUnits.at(i)->nextTile();
				// Checks if the Enemy is on the last Tile, which is Tile of index 62.
				if (this->listUnits.at(i)->getTile() == 62) {
					// Deals damage to the Player based on its assigned damage, internally checks the loss condition.
					p.hurt(this->listUnits.at(i)->getDamage(), w);
					// Safely empties the vector if there is only one item, or erases the current Enemy.
					if (this->listUnits.size() == 1) {
						this->listUnits.clear();
					}
					else {
						this->listUnits.erase(this->listUnits.begin() + i);
					}
					// Checks for the win condition after this despawn.
					if (p.checkEndWave(this->listUnits, units, this->listWaves.at(0)->getNumEnemies())) {
						if (this->listWaves.size() == 1) {
							this->listWaves.clear();
						}
						else {
							this->listWaves.erase(this->listWaves.begin());
						}
						p.checkWin(w, this->listWaves);
					}
				}
			}
			// Moves the current Enemy by the given offset, and based on the current Tile it is on.
			if (this->listUnits.size() > 0) {
				this->listUnits.at(i)->updateMove(m.getSpecificTile(this->listUnits.at(i)->getTile()));
			}
		}
	}

	/*
		Function: drawGame
		
		Description: This function draws all objects on the screen to be displayed.
		Precondition: RenderWindow w is currently open.
		Postcondition: All of the current objects being stored have been displayed to the screen.
	*/
	void drawGame(sf::RenderWindow& w, Player p) {
		w.clear();
		// Draws the map
		w.draw(this->background);
		// Draws every Enemy on screen and every Tower on screen
		int sizeE = this->listUnits.size(), sizeT = this->listTowers.size();
		for (int i = 0; i < sizeE; i++) {
			this->listUnits.at(i)->drawEnemy(w);
		}
		for (int j = 0; j < sizeT; j++) {
			this->listTowers.at(j)->drawTower(w);
		}
		for (int k = 0; k < this->listProjectiles.size(); k++) {
			this->listProjectiles.at(k)->drawProjectile(w);
		}
		w.display();
	}

	// Adds a new Enemy object to be stored into the vector.
	void addUnit() {
		Enemy* unit = new Enemy(sf::Vector2f(50, 50), sf::Vector2f(25, 725), this->listWaves.at(0)->getEnemyHP(), 3);

		this->listUnits.push_back(unit);
	}

	/*
		Function: addTower
		
		Description: This function creates a new Tower (currently only creates FireTowers), and checks if the Tower is being placed in a
		valid position. If the position is valid, it stores the new Tower into the vector.
		Precondition: Map, RenderWindow have proper values and states, x and y are at the position of the Mouse upon click.
		Postcondition: A new Tower is stored to the vector if it passes the requirements.
	*/
	bool addTower(Map m, sf::RenderWindow& w, double x, double y, int type) {
		Tower* t;

		if (type == 0) {
			t = new FireTower(x, y);
		}
		else {
			t = new LightningTower(x, y);
		}

		if (t->placeTower(m, w, x, y) && !collidesAnyTower(t)) {
			this->listTowers.push_back(t);
			return true;
		}
		return false;
	}

	/*
		Function: collidesAnyTower
		
		Description: This function iterates through the current list of Towers, and if the new Tower would intersect any of them, it returns true.
		Returns false otherwise.
		Precondition: Tower t != nullptr
		Postcondition: The correct return value is reached.
	*/
	bool collidesAnyTower(Tower* t) {
		int size = this->listTowers.size();

		for (int i = 0; i < size; i++) {
			if (t->getHitbox().getGlobalBounds().intersects(this->listTowers.at(i)->getHitbox().getGlobalBounds())) {
				return true;
			}
		}
		return false;
	}

	void readWaves() {
		std::ifstream input("waves.csv");
		size_t pos = 0;
		std::string line, token;
		int start = 0;

		getline(input, line);
		while (!input.eof()) {
			Wave* curWave = new Wave();

			getline(input, line);
			curWave->setNumEnemies(stoi(readToComma(line)));
			curWave->setHP(stoi(readToComma(line)));
			curWave->setSpacing(stoi(readToComma(line)));

			this->listWaves.push_back(curWave);
		}

	}

	std::string readToComma(std::string& line) {
		std::string token = "";
		size_t pos = line.find(",");
		if (pos == std::string::npos) {
			return line;
		}
		else {
			token = line.substr(0, pos);
		}
		line.erase(0, pos + 1);

		return token;
	}

	// Private attributes, storing the objects, as well as the map background and wave information.
	std::vector<Enemy*> listUnits;
	std::vector<Tower*> listTowers;
	std::vector <Wave*> listWaves;
	std::vector <Projectile*> listProjectiles;
	sf::Texture image;
	sf::Sprite background;
};
