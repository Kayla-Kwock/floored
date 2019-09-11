#include "stdafx.h"

Projectile::Projectile(std::string name_) {
	/*active = false;
	dead = false;
	x = y = -9999;
	float xscale = 1;
	float yscale = 1;
	stats info = getStats(name_);
	//Begin Player Weapons
	if (name_ == "Pistol") {
		this->texture.loadFromFile("Sprites/streaker.png");
	}
	else if (name_ == "Sniper") {
		this->texture.loadFromFile("Sprites/streaker.png");
		sprite.setColor(sf::Color::Red);
	}
	else if (name_ == "Cat Gun") {
		this->texture.loadFromFile("Sprites/Cat Gun_p.png");
		xscale = 0.05;
		yscale = 0.05;
	}
	else if (name_ == "Minigun") {
		this->texture.loadFromFile("Sprites/streaker.png");
		sprite.setColor(sf::Color::Blue);
	}
	else if (name_ == "Needler") {
		this->texture.loadFromFile("Sprites/Needler_p.png");
	}//End Player Weapons
	//Begin Turrets
	else if (name_ == "Peashooter") {
		this->texture.loadFromFile("Sprites/Peashooter_p.png");
	}
	else if (name_ == "Heavy Machine Gun") {
		this->texture.loadFromFile("Sprites/streaker.png");
		sprite.setColor(sf::Color::White);
	}
	else if (name_ == "Tachanka") {
		this->texture.loadFromFile("Sprites/streaker.png");
		sprite.setColor(sf::Color::Yellow);
	}
	else if (name_ == "Railgun") {
		this->texture.loadFromFile("Sprites/streaker.png");
		sprite.setColor(sf::Color::Blue);
	}
	else if (name_ == "Lazer Turret") {
		this->texture.loadFromFile("Sprites/Lazer Turret_p.png");
	}
	// Don't modify these lines
	damage = info.damage;
	speed = info.bullet_speed;
	punch_ref = info.punch;
	punch = punch_ref;
	sprite.setScale(xscale, yscale);
	sprite.setTexture(texture);
	sf::Vector2u size = texture.getSize();
	spLength = abs(size.x * xscale);
	spHeight = abs(size.y * yscale);*/
}

Projectile::Projectile(std::string name_, int level) {
	active = false;
	dead = false;
	float xscale = 1;
	float yscale = 1;
	x = y = -9999;
	stats info = getUpgrade(name_,level);
	//Begin Player Weapons
	if (name_ == "Pistol") {
		this->texture.loadFromFile("Sprites/streaker.png");
		sprite.setColor(sf::Color::White);
	}
	else if (name_ == "Sniper") {
		this->texture.loadFromFile("Sprites/streaker.png");
		sprite.setColor(sf::Color::Red);
	}
	else if (name_ == "Cat Gun") {
		this->texture.loadFromFile("Sprites/Cat Gun_p.png");
		xscale = 0.1;
		yscale = 0.2;
	}
	else if (name_ == "Minigun") {
		this->texture.loadFromFile("Sprites/streaker.png");
		sprite.setColor(sf::Color::Blue);
	}
	else if (name_ == "Needler") {
		this->texture.loadFromFile("Sprites/Needler_p.png");
	}//End Player Weapons
	 //Begin Turrets
	else if (name_ == "Peashooter") {
		this->texture.loadFromFile("Sprites/Peashooter_p.png");
	}
	else if (name_ == "Heavy Machine Gun") {
		this->texture.loadFromFile("Sprites/streaker.png");
		sprite.setColor(sf::Color::White);
	}
	else if (name_ == "Tachanka") {
		this->texture.loadFromFile("Sprites/streaker.png");
		sprite.setColor(sf::Color::Yellow);
	}
	else if (name_ == "Railgun") {
		this->texture.loadFromFile("Sprites/streaker.png");
		sprite.setColor(sf::Color::Blue);
	}
	else if (name_ == "Lazer Turret") {
		this->texture.loadFromFile("Sprites/Lazer Turret_p.png");
	}
	// Don't modify these lines
	damage = info.damage;
	speed = info.bullet_speed;
	punch = punch_ref = info.punch;
	sprite.setScale(xscale, yscale);
	sprite.setTexture(texture);
	sf::Vector2u size = texture.getSize();
	spLength = abs(size.x * xscale);
	spHeight = abs(size.y * yscale);
}

int Projectile::getPunch() {
	return this->punch;
}

int Projectile::getDamage() {
	return this->damage;
}

void Projectile::setPunch(int newPunch) {
	this->punch = newPunch;
}

void Projectile::setActive(int playerXR, int playerC, int floor_) {
	x = playerXR;
	y = playerC;
	floor = floor_;
	sprite.setPosition(x, y);
	active = true;
}

void Projectile::revive() {
	punch = punch_ref;
	active = false;
	dead = false;
}