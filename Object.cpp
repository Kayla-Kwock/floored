#include "stdafx.h"

sf::Sprite& Object::getSprite() {
	sf::Sprite& ref = sprite;
	return ref;
}

int Object::getXL() {
	return this->x;
}

int Object::getYU() {
	return this->y;
}

int Object::getXR() {
	return (this->x + this->spLength);
}

int Object::getYD() {
	return (this->y + this->spHeight);
}

int Object::getYC() {
	return(this->spHeight / 2 + this->y);
}

void Object::setSpriteDimensions(sf::Texture texture_) {
	spLength = texture_.getSize().x;
	spHeight = texture_.getSize().y;
}