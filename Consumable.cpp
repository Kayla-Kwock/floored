#include "stdafx.h"

// Default constructor, only used for Global.cpp
Consumable::Consumable() {}

// The most common constructor used
Consumable::Consumable(std::string name_, int floor_, int slot) {
	stats info = getStats(name_);
	float xscale = 1;
	float yscale = 1;
	//Depending on the name given, different stats
	//	are applied to the consumable
	if (name_ == "Mine") {
		interaction_type = "damage";
		usage = "once";
		damage = info.damage;
		texture.loadFromFile("Sprites/mine.png");
		dead_texture = texture;
	}
	else if (name_ == "Wall"){
		interaction_type = "block";
		usage = "many";
		max_hp = current_hp = info.hp;
		texture.loadFromFile("Sprites/wall.png");
		dead_texture.loadFromFile("Sprites/wall_dead.png");
	}
	else if (name_ == "Bandit Wire") {
		interaction_type = "damage";
		usage = "many";
		texture.loadFromFile("Sprites/Bandit Wire.png");
		dead_texture = texture;
		xscale = 0.05;
		yscale = 0.03;
	}
	else if (name_ == "Buzzsaw") {
		interaction_type = "block/damage";
		usage = "many";
		max_hp = current_hp = info.hp;
		texture.loadFromFile("Sprites/Buzzsaw.png");
		dead_texture = texture;
		xscale = 0.07;
		yscale = 0.07;
	}
	else if (name_ == "Gulper") {
		interaction_type = "damage";
		usage = "once";
		max_hp = current_hp = info.hp;
		texture.loadFromFile("Sprites/Gulper.png");
		dead_texture = texture;
		xscale = 0.25;
		yscale = 0.25;
	}
	//Place the x-coordinate of the origin depending on what
	//	slot it is in
	switch (slot) {
		case(1):
			this->x = 600;
			break;
		case(2):
			this->x = 900;
	}
	//Set the attributes of the consumable
	active = true; //Activate it
	floor = floor_; //Set what floor it's on
	setSpriteDimensions(texture);//Set sprite dimensions
	sprite.setTexture(texture);
	sprite.setScale(xscale, yscale);
	sf::Vector2u size = texture.getSize();
	spLength = abs(size.x * xscale);
	spHeight = abs(size.y * yscale);
	//Set the y-coordinate of the origin based on sprite height
	y = place_on_floor(floor_, spHeight);
	sprite.setPosition(x, y);
	this->slot_num = slot;
	name = name_;
	level = 1;
}

//Triggers the ability of the consumable
void Consumable::activate(Enemy& enemy, float delta) {
	bool killed = false;
	playSFX(name);//Plays the sound effect with the consumable
	//Depending on the interaction type of the consumable, do things
	if (this->interaction_type == "damage") {
		//Deal damage to the enemy
		if (this->damage >= enemy.getHP()) {//If the damage will kill the enemy
			enemy.setHP(0);
			enemy.setDead();
		}
		else(enemy.setHP(enemy.getHP() - this->damage));//Else simply do damage
	}
	else if (this->interaction_type == "block") {
		//Stop the enemy from advancing
		if (this->current_hp >= enemy.getDamage()) {//If consumable will survive attack
			this->setHP(enemy.getDamage());
			//Move the enemy back, effectively canceling out their forward movement
			enemy.moveRight(delta);
		}
		else killed = true;//Else the consumable is killed
	}
	else if (this->interaction_type == "block/damage") {//Does both damage and block
		if (this->current_hp >= enemy.getDamage()) {
			this->setHP(enemy.getDamage());
			enemy.setHP(enemy.getHP() - this->damage);
			enemy.moveRight(delta);
		}
		else killed = true;
	}
	//Depending on the usage type, determine if the consumable should be deactivated
	if (usage == "once") {//Always deactivate if the consumable is one-time use
		sprite.setTexture(dead_texture);
		sprite.setColor(sf::Color::Red);
		this->active = false;
	}
	else if (usage == "many") {//If it can be used many times (walls)
		if (killed) {//If killed was set to true in earlier stages, kill it
			sprite.setTexture(dead_texture);
			sprite.setColor(sf::Color::Red);
			this->active = false;
		}
	}
}

//Refreshes the consumable into an active state at
//	full HP if applicable
void Consumable::reload() {
	stats info = getUpgrade(name, level);
	sprite.setTexture(texture);
	active = true;
	if (name == "Wall" || name == "Buzzsaw") {
		current_hp = max_hp;
	}
}

//Increases the consumable's level and appropriate stats
void Consumable::upgrade() {
	level++;
	stats info = getUpgrade(name, level);
	if (name != "Wall") {
		damage = info.damage;
	}
	if (name == "Wall" || name == "Buzzsaw") {
		max_hp = info.hp;
	}
	reload();//Make sure the changes are applied
}

//Getters and setters for internal variables
bool Consumable::isActive() {
	return active;
}

void Consumable::setHP(int damage) {
	this->current_hp -= damage;
}
