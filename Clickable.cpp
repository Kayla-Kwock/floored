#include "stdafx.h"

//Creates transparent clickables
Clickable::Clickable(int x_, int y_, int length_, int height_,std::string function_) : turret(turret_master), consumable(consumable_master){
	shape = sf::RectangleShape(sf::Vector2f(length_, height_));
	shape.setPosition(x_, y_);
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Blue);
	shape.setOutlineThickness(-3);
	function = function_;
}

//Creates clickables with text inside
Clickable::Clickable(
	int x_,
	int y_, 
	int length_, 
	int height_, 
	std::string text_, 
	sf::Font& font_, 
	int text_size_): turret(turret_master), consumable(consumable_master) {
	int outlineThickness = -3;
	shape = sf::RectangleShape(sf::Vector2f(length_, height_));
	shape.setPosition(x_, y_);
	shape.setFillColor(sf::Color::Black);
	shape.setOutlineColor(sf::Color::Blue);
	shape.setOutlineThickness(outlineThickness);
	text = sf::Text(text_, font_, text_size_);
	function = text_;
	//Centers the text inside the shape
	text.setPosition(
		(x_ + shape.getLocalBounds().width/2 - text.getLocalBounds().width/2), 
		floor(y_ + 2*outlineThickness + shape.getLocalBounds().height/2 - 1.75*(text.getLocalBounds().height/2)));
}

//Creates the turret/consumable upgrade squares
Clickable::Clickable(GameManager& gm, int floor, int slot, std::string ConsOrTurret, sf::Color color, int outlineThickness):
	turret(turret_master), consumable(consumable_master) {
	if (ConsOrTurret == "Turret") {//If the square is supposed to be for turrets
		//If there are no turrets at the current floor
		if (gm.getFloors().at(floor).get().getTurrets().empty()) {
			//All squares will build a turret
			function = "buildTurret";
			}
		else {//Else determine which squares should be upgrades and which should be build per floor
			for (std::size_t i = 0; i < gm.getFloors().at(floor).get().getTurrets().size(); i++) {
				if (gm.getFloors().at(floor).get().getTurrets().at(i).getSlot() == slot) {
					function = "upgradeTurret";
					turret = gm.getFloors().at(floor).get().getTurrets().at(i);
					break;
				}
				else function = "buildTurret";
			}
		}
		//Create and position the upgrade square
		shape = sf::RectangleShape(sf::Vector2f(50, 50));
		shape.setPosition(150 + (slot-1) * 75 - 10, place_on_floor(floor + 1, 50));
	}
	//Do the same thing for Consumables (read above for details)
	else if (ConsOrTurret == "Cons") {
		if (gm.getFloors().at(floor).get().getConsumables().empty()) {
			function = "buildConsumable";
		}
		else {
			for (std::size_t i = 0; i < gm.getFloors().at(floor).get().getConsumables().size(); i++) {
				if (gm.getFloors().at(floor).get().getConsumables().at(i).getSlot() == slot) {
					function = "upgradeConsumable";
					consumable = gm.getFloors().at(floor).get().getConsumables().at(i);
					name = gm.getFloors().at(floor).get().getConsumables().at(i).getName();
					break;
				}
				else function = "buildConsumable";
			}
		}
			shape = sf::RectangleShape(sf::Vector2f(50, 50));
			shape.setPosition(580 + (slot - 1) * 300, place_on_floor(floor + 1, 50));
	}
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(color);
	shape.setOutlineThickness(outlineThickness);
}

//Draws the text and the square of a clickable to the window
void Clickable::draw(sf::RenderTarget& window, sf::RenderStates states) const{
	window.draw(shape);
	window.draw(text);
}

//Adds functionality to start and exit buttons
void Clickable::activate(GameManager& gm){
	if (function == "exit") {
		gm.getWindow().close();
	}
	else if (function == "start") {
		gm.setNextWave();
	}
}

//Adds functionality to turret/consumable squares
void Clickable::activate(GameManager& gm, int selected_menu, std::string name_) {//For gameplay options
	int floor_ = floor(selected_menu / 5);
	int slot = (selected_menu % 5) + 1;
	if (function == "buildTurret") {
		gm.getFloors().at(floor_).get().build_turret(name_, slot);
	}
	else if (function == "buildConsumable") {
		gm.getFloors().at(floor_).get().build_consumable(name_, slot % 3);
	}
}

//Getters for variables of a clickable
sf::Text& Clickable::getText() {
	return text;
}

sf::RectangleShape& Clickable::getShape() {
	return shape;
}

std::string Clickable::getFunction() {
	return function;
}

Turret& Clickable::getTurret() {
	return turret;
}

std::string Clickable::getName() {
	return name;
}

Consumable& Clickable::getConsumable() {
	return consumable;
}