#include "stdafx.h"

//Constructor for an enemy
Enemy::Enemy(int floor_, std::string name_) {
	stats info = getStats(name_);
	floor = floor_;
	active = false;
	//Assigns specific attributes to enemy depending
	//	on the name given
	if (name_ == "Ghost") {
		xscale = 0.04;
		yscale = 0.04;
		texture.loadFromFile("Sprites/orange_ghost.png");
		//Color white means default colors for the texture
		//	This line was added in-case we wanted to use recolored textures
		sprite.setColor(sf::Color::White);
	}
	else if (name_ == "Hunter") {
		xscale = 0.12;
		yscale = 0.12;
		texture.loadFromFile("Sprites/blue_ghost.png");
		sprite.setColor(sf::Color::White);
	}
	else if (name_ == "Harpy") {
		xscale = 0.03;
		yscale = 0.03;
		texture.loadFromFile("Sprites/harpy.png");
		sprite.setColor(sf::Color::White);
	}
	else if (name_ == "Tank") {
		xscale = 0.04;
		yscale = 0.04;
		texture.loadFromFile("Sprites/red_ghost.png");
		sprite.setColor(sf::Color::White);
	}
	else if (name_ == "Wizard") {
		xscale = 0.75;
		yscale = 0.75;
		texture.loadFromFile("Sprites/Tep.png");
		sprite.setColor(sf::Color::White);
	}
	//Set the stats, texture, and origin of enemies
	hp = info.hp;
	damage = info.damage;
	speed = info.enemy_speed;
	thickness = info.thickness;
	money = info.money;
	this->sprite.setTexture(texture);
	sprite.setScale(xscale, yscale);
	sf::Vector2u size = texture.getSize();
	spLength = abs(size.x * xscale);
	spHeight = abs(size.y * yscale);
	x = y = 0;//Sets origin
}

//Activates the enemy
void Enemy::setActive(sf::RenderWindow& window) {
	//Sets the origin of the enemy based on window size
	//	and what floor the enemy is spawning on
	x = window.getSize().x;
	y = place_on_floor(floor, spHeight);
	sprite.setPosition(x, y);
	active = true;
}

//Getter and Setter for enemy HP
int Enemy::getHP() {
	return this->hp;
}

void Enemy::setHP(int newHP) {
	this->hp = newHP;
}

//Getter for enemy thickness
int Enemy::getThickness() {
	return this->thickness;
}

//Getter for enemy damage
int Enemy::getDamage() {
	return this->damage;
}

//Getter for enemy money
int Enemy::dropMoney() {
	return money;
}