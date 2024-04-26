#pragma once
#include "Enemy.hpp"
#include <math.h>


class Projectile {
public:
	Projectile(sf::Vector2f pos, int damage, int origin, int type) {
		this->type = type;
		if (this->type == 0) {
			this->t.loadFromFile("FireBullet.png");
		}
		else {
			this->t.loadFromFile("Lightning_Projectile.png");
		}
		this->bullet.setRadius(20);
		this->bullet.setPosition(pos);
		this->bullet.setTexture(&t);
		this->target = nullptr;
		this->damage = damage;
		this->originTower = origin;
	}

	void updatePosition() {
		double a = this->bullet.getPosition().x - this->target->getHitbox().getPosition().x;
		double b = this->bullet.getPosition().y - this->target->getHitbox().getPosition().y;
		double c = sqrt(pow(a, 2) + pow(b, 2));
		double angle = atan2(b, a) * (180 / 3.14159);

		bullet.move(8 * (-a / c), 8 * (-b / c));
		bullet.setRotation(180 + angle);
	}

	sf::CircleShape getBullet() {
		return this->bullet;
	}

	Enemy* getTarget() {
		return this->target;
	}

	void setTarget(Enemy* newTarget) {
		this->target = newTarget;
	}

	void drawProjectile(sf::RenderWindow& w) {
		w.draw(this->bullet);
	}

	int getDamage() {
		return this->damage;
	}

	int getOrigin() {
		return this->originTower;
	}
private:
	sf::CircleShape bullet;
	sf::Texture t;
	Enemy* target;
	int damage;
	int originTower;
	int type;
};