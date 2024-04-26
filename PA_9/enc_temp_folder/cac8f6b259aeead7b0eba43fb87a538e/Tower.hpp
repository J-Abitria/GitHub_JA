#include "Enemy.hpp"

class Tower {
public:
	Tower(double x, double y) {
		this->damage = 1;
		this->hitbox.setSize(sf::Vector2f(50, 50));
		this->hitbox.setPosition(sf::Vector2f(x, y));
		this->target = new Enemy();
	}

	void findTarget(std::vector<Enemy*> list) {
		this->target = list.front();
	}

	void fire(std::vector<Enemy*> list) {
		this->findTarget(list);
		this->target->hurt(this->damage);

		if (!target->isAlive()) {
			list.erase(list.begin());
		}
	}

	bool placeTower(Map m, sf::RenderWindow& w, double x, double y) {
		int index = 0;

		if (!m.intersectsPath(this->hitbox, index)) {
			if (0 <= x <= 1000 && 0 <= y <= 1000) {
				this->hitbox.setFillColor(sf::Color::Black);
				return true;
			}
		}
		return false;
	}

	sf::RectangleShape getHitbox() {
		return this->hitbox;
	}

	void drawTower(sf::RenderWindow& w) {
		w.draw(this->hitbox);
	}
private:
	sf::RectangleShape hitbox;
	int damage;
	Enemy* target;
};