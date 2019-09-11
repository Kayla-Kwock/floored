#include "stdafx.h"

Player::Player(){
	texture.loadFromFile("Sprites/player.png");
	sprite.setTexture(texture);
	x = 0;
	y = 134;
	floor = 1;
	speed = 500;
	setSpriteDimensions(texture);
	sprite.setPosition(x, y);
}

void Player::switch_weapons() {
	std::reference_wrapper<Firearm> temp = equipped;
	equipped = holstered;
	holstered = temp;
}

void Player::swap_equipped(Firearm& firearm) {
	equipped = firearm;
}

void Player::swap_holstered(Firearm& firearm) {
	holstered = firearm;
}

void Player::shoot_equipped() {
	equipped.get().shoot(this->getXR(), this->getYD(), this->spHeight, this->floor);
}

Firearm& Player::getEquipped() {
	Firearm& ref = equipped;
	return ref;
}

Firearm& Player::getHolstered() {
	Firearm& ref = holstered;
	return ref;
}

void Player::setMoney(int money_) {
	money = money + money_;
}

int Player::getMoney() {
	return money;
}