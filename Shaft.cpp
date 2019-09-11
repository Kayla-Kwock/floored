#include "stdafx.h"

Shaft::Shaft() {
	texture.loadFromFile("GameField/Shaft.png");
	sprite.setPosition(0, 134);
	setSpriteDimensions(texture);
	sprite.setTexture(texture);
}

int Shaft::getHP() {
	return current_hp;
}

void Shaft::setHP(int damage) {
	current_hp -= damage;
}

void Shaft::resetHP(){
	current_hp = max_hp;
}

bool Shaft::dead() {
	return (current_hp <= 0);
}

void Shaft::drawHP(sf::RenderWindow& window){
	sf::RectangleShape outline, healthbar;
	outline.setPosition(140, 100);
	outline.setSize(sf::Vector2f(1000,20));
	outline.setFillColor(sf::Color::Red);
	healthbar = outline;
	healthbar.setSize(sf::Vector2f(1000*(double(current_hp/max_hp)), 20));
	healthbar.setFillColor(sf::Color::Green);
	window.draw(outline);
	window.draw(healthbar);
}