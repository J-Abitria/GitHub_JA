#include "Game.hpp"

/*
Game needs to load map, set starting variables, and run game
*/
Game::Game()
{

}

Game::~Game() {

}

//runs game functions
void Game::runGame()
{
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Hold The Place");
	Map m;
	Player p;
	this->unitsInWave = 10;
	//put all the stuff that does time here
	window.setFramerateLimit(60);
	loadMap();
	int frame = 0, units = 0;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				this->addTower(m, window, sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
			}
		}
		if (frame % 30 == 0 && units < this->unitsInWave) {
			this->addUnit();
			units++;
		}
		//each "time": 
		if (frame % 60 == 0 && !this->listUnits.empty()) {
			for (int i = 0; i < this->listTowers.size(); i++) {
				if (!this->listUnits.empty()) {
					this->listTowers.at(i)->fire(this->listUnits);
				}
			}
			p.checkWin(window, this->listUnits, units, this->unitsInWave);
		}
		updateGame(m, p, window, units);
		drawGame(window);
		frame++;
	}
}

void Game::loadMap()
{
	this->image.loadFromFile("Map_Background.png");
	this->background.setTexture(this->image);
}

void Game::addTower(Map m, sf::RenderWindow& w, double x, double y) {
	Tower* t = new FireTower(x, y);
	
	if (t->placeTower(m, w, x, y) && !collidesAnyTower(t)) {
		this->listTowers.push_back(t);
	}
}

bool Game::collidesAnyTower(Tower* t) {
	int size = this->listTowers.size();

	for (int i = 0; i < size; i++) {
		if (t->getHitbox().getGlobalBounds().intersects(this->listTowers.at(i)->getHitbox().getGlobalBounds())) {
			return true;
		}
	}
	return false;
}


void Game::updateGame(Map m, Player& p, sf::RenderWindow& w, int units)
{
	updateUnit(m, p, w, units);
}

void Game::addUnit() {
	Enemy* unit = new Enemy(sf::Vector2f(50, 50), sf::Vector2f(25, 725), 3, 3);

	this->listUnits.push_back(unit);
}


void Game::updateUnit(Map m, Player& p, sf::RenderWindow& w, int units)
{
	//use vector of units to update each unit
	//start loop location
	for (int i = 0; i < this->listUnits.size(); i++) //goes through entire vector
	{
		bool deleted = false; //check to prevent iterating if we deleted instead
		
		if (this->listUnits.at(i)->getMovements() > 0 && this->listUnits.at(i)->getMovements() % 25 == 0) {
			this->listUnits.at(i)->nextTile();
			if (this->listUnits.at(i)->getTile() == 62) {
				p.hurt(this->listUnits.at(i)->getDamage(), w);
				if (this->listUnits.size() == 1) {
					this->listUnits.clear();
				}
				else {
					this->listUnits.erase(this->listUnits.begin() + i);
				}
				p.checkWin(w, this->listUnits, units, this->unitsInWave);
			}

		}
		if (this->listUnits.size() > 0) {
			this->listUnits.at(i)->updateMove(m.getSpecificTile(this->listUnits.at(i)->getTile())); //class function of unit to update; does everything we want to happen to unit (move, isAlive check, etc)
		}
	}
}


void Game::drawGame(sf::RenderWindow& w) {
	w.clear();
	w.draw(this->background);
	int sizeE = this->listUnits.size(), sizeT = this->listTowers.size();
	for (int i = 0; i < sizeE; i++) {
		this->listUnits.at(i)->drawEnemy(w);
	}
	for (int j = 0; j < sizeT; j++) {
		this->listTowers.at(j)->drawTower(w);
	}
	w.display();
}