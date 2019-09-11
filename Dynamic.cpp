#include "stdafx.h"

//Sets the object's origin points
void Dynamic::setX(int XL) {
	x = XL;
}

void Dynamic::setY(int YU) {
	y = YU;
}

//Getter for object's speed
int Dynamic::getSpeed() {
	return speed;
}

//Getter and setter for object's floor
int Dynamic::getFloor() {
	return this->floor;
}

void Dynamic::setFloor(int floor_) {
	this->floor = floor_;
}

//Basic movement functions for object
void Dynamic::moveRight(float delta) {
	x += ceil(speed * delta);
	this->sprite.setPosition(this->x, this->y);
}

void Dynamic::moveLeft(float delta) {
	x -= ceil(speed * delta);
	this->sprite.setPosition(this->x, this->y);
}

void Dynamic::moveUp(float delta) {
	y -= speed * delta;
	this->sprite.setPosition(this->x, this->y);
}

void Dynamic::moveDown(float delta) {
	y += speed * delta;
	this->sprite.setPosition(this->x, this->y);
}

void Dynamic::moveUpFloor() {
	if (floor <= 1) {} //can't move up any further, so do nothing
	else {
		this->y -= 100;
		this->floor -= 1;
		this->sprite.setPosition(this->x, this->y);
	}
}

void Dynamic::moveDownFloor() {
	if (floor >= 5) {}//Can't move down any further, so do nothing
	else {
		this->y += 100;
		this->floor += 1;
		this->sprite.setPosition(this->x, this->y);
	}
}

//Getter and Setter for Active and Dead
bool Dynamic::isActive() {
	return this->active;
}

void Dynamic::setActive() {
	this->active = true;
}

bool Dynamic::isDead() {
	return this->dead;
}

bool Dynamic::isNotDead() {
	return !dead;
}

void Dynamic::setDead() {
	this->dead = true;
}
