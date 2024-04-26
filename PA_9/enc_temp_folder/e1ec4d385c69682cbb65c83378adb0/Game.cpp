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
	Enemy* checkUnit = new Enemy(sf::Vector2f(50, 50), sf::Vector2f(0, 700));
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
		}
		if (frame % 120 == 0 && units < 5) {
			this->addUnit();
			units++;
		}
		//each "time": 
		updateGame(m);
		drawGame(window);
		frame++;
	}
}

void Game::loadMap()
{
	this->image.loadFromFile("Map_Background.png");
	this->background.setTexture(this->image);
}


void Game::updateGame(Map m)
{
	updateUnit(m);
}

void Game::addUnit() {
	Enemy unit(sf::Vector2f(50, 50), sf::Vector2f(0, 700));

	this->listUnits.push_back(unit);
}


void Game::updateUnit(Map m)
{
	//use vector of units to update each unit
	//start loop location
	/*
	if ((checkUnit->getMovements() > 0 && checkUnit->getMovements() % 50 == 0) && checkUnit->getTile() < 62) {
		checkUnit->nextTile();
	}
	checkUnit->updateMove(m.getSpecificTile(checkUnit->getTile()));
	*/
	for (int i = 0; i < this->listUnits.size(); i++) //goes through entire vector
	{
		bool deleted = false; //check to prevent iterating if we deleted instead
		
		if (this->listUnits.at(i).getMovements() > 0 && this->listUnits.at(i).getMovements() % 25 == 0) {
			this->listUnits.at(i).nextTile();
			if (this->listUnits.at(i).getTile() == 62) {
				if (this->listUnits.size() == 1) {
					this->listUnits.clear();
				}
				else {
					this->listUnits.erase(this->listUnits.begin() + i);
				}
			}
		}
		this->listUnits.at(i).updateMove(m.getSpecificTile(this->listUnits.at(i).getTile())); //class function of unit to update; does everything we want to happen to unit (move, isAlive check, etc)

		/*
		if ((*checkUnit)->isAlive() == false) //unit died; delete it
		{
			checkUnit = listUnits.erase(checkUnit); //moves to next unit after erasing current
			deleted = true;
		}

		if (deleted == false)
		{
			checkUnit++;
		}
		*/
	}
}


void Game::drawGame(sf::RenderWindow& w) {
	w.clear();
	w.draw(this->background);
	int size = this->listUnits.size();
	for (int i = 0; i < size; i++) {
		this->listUnits.at(i).drawEnemy(w);
	}
	w.display();
}