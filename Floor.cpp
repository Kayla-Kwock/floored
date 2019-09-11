#include "stdafx.h"

//Constructor for a Floor object
Floor::Floor(int floor_) {
	floor_num = floor_;//Set the floor number
	//Originally, each floor would be individually and uniquely marked
	//	However, we ran out of time. This is legacy if we decide to 
	//	Implement in the future
	switch (floor_num) {
		case(1):
			texture.loadFromFile("GameField/Floor1.png");
			break;
		case(2):
			texture.loadFromFile("GameField/Floor1.png");
			break;
		case(3):
			texture.loadFromFile("GameField/Floor1.png");
			break;
		case(4):
			texture.loadFromFile("GameField/Floor1.png");
			break;
		case(5):
			texture.loadFromFile("GameField/Floor1.png");
	}
	//Set the position of the floor
	sprite.setPosition(100, 100 * (floor_num - 1) + 134);
	sprite.setTexture(texture);
}

//Adds a turret into the turret vector of the floor
void Floor::build_turret(std::string name_, int slot_) {
	bool occupied = false;
	//Check if any turret has the same slot numebr
	for (std::size_t i = 0; i < turrets.size(); i++) {
		if (turrets[i].getSlot() == slot_) {
			occupied = true;
			break;
		}
	}
	if (!occupied) {
		//if the slot is currently occupied, you can't build another one
		//if it's not, go build one!
		turrets.push_back(*new Turret(name_, floor_num, slot_));
	}
}

//Adds a consumable into the consumable vector of the floor
void Floor::build_consumable(std::string name_, int slot) {
	bool occupied = false;
	//Check if any consumable has the same slot numebr
	for (std::size_t i = 0; i < consumables.size(); i++) {
		if (consumables[i].getSlot() == slot) {
			occupied = true;
			break;
		}
	}
	if (!occupied) {
		//if the slot is currently occupied, you can't build another one
		//if it's not, go build one!
		consumables.push_back(*new Consumable(name_, floor_num, slot));
	}
}

//Deletes a turret at specified location in vector
//Note: This slot means the iterator that the turret is represented by
//		not what slot the turret occupies in the game field
void Floor::delete_turret(int slot) {
	turrets.erase(turrets.begin() + (slot));
}

//Deletes a consumable at the specified location in vector
//Note: Same note as delete_turret
void Floor::delete_consumable(int slot) {
	consumables.erase(consumables.begin() + (slot));
}

//Getters for references to the turrets, consumables, and enemies of the floor
std::vector<Enemy>& Floor::getEnemies() {
	std::vector<Enemy>& ref = enemies;
	return ref;
}

std::vector<Turret>& Floor::getTurrets() {
	std::vector<Turret>& ref = turrets;
	return ref;
}

std::vector<Consumable>& Floor::getConsumables() {
	std::vector<Consumable>& ref = consumables;
	return ref;
}
