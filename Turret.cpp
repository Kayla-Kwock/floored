#include "stdafx.h"

Turret::Turret() {}

Turret::Turret(std::string name_, int floor_, int slot_) {
	float xscale = 1;
	float yscale = 1;
	if (name_ == "Peashooter") {
		texture.loadFromFile("Sprites/Peashooter.png");
		firearm = Firearm("Peashooter");
		xscale = 0.35;
		yscale = 0.35;
	}
	else if (name_ == "Heavy Machine Gun") {
		texture.loadFromFile("Sprites/Heavy Machine Gun.png");
		firearm = Firearm("Heavy Machine Gun");
		xscale = 0.2;
		yscale = 0.2;
	}
	else if (name_ == "Tachanka") {
		texture.loadFromFile("Sprites/Tachanka.png");
		firearm = Firearm("Tachanka");
		xscale = 0.15;
		yscale = 0.15;
	}
	else if (name_ == "Railgun") {
		texture.loadFromFile("Sprites/Railgun.png");
		firearm = Firearm("Railgun");
		xscale = 0.04;
		yscale = 0.04;
	}
	else if (name_ == "Lazer Turret") {
		texture.loadFromFile("Sprites/Lazer Turret.png");
		firearm = Firearm("Lazer Turret");
		xscale = 0.03;
		yscale = 0.03;
	}

	sprite.setTexture(texture);
	setSpriteDimensions(texture);
	slot_num = slot_;
	switch (slot_) {
	case(1):
		this->x = 150;
		break;
	case(2):
		this->x = 225;
		break;
	case(3):
		this->x = 300;
	}
	sprite.setScale(xscale, yscale);
	sf::Vector2u size = texture.getSize();
	spLength = abs(size.x * xscale);
	spHeight = abs(size.y * yscale);
	this->y = place_on_floor(floor_, spHeight);
	sprite.setPosition(x, y);
	floor = floor_;
	name = name_;
	level = 1;
}

int Turret::getLevel(){//Gets the current level of the turret
	return level;
}

Firearm& Turret::getFirearm() {
	Firearm& ref = this->firearm;
	return ref;
}

void Turret::shoot() {
	firearm.shoot(getXR(), getYD(), spHeight, floor);
}

void Turret::upgrade() {
	level++;
	firearm.setLevel(level);
}
