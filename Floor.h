#pragma once

#include  "stdafx.h"
/* Each one of the five floors of the game is a Floor
 * The vectors hold all the components vital to the floor
 *	all the enemies, turrets, and consumables specific to that floor
 * floor_num is what floor number it is in the game
 */

class Floor : public Object{
protected:
	std::vector<Enemy> enemies;
	std::vector<Turret> turrets;
	std::vector<Consumable> consumables;
	int floor_num;
public:

	/*
	* Brief: Constructor for a Floor
	* Param: A floor number
	* Return: None
	*/
	Floor(int floor_);

	/*
	* Brief: Constructs a turret 
	* Param: The name of the turret and what slot it goes into 
	*	1,2,3: 1 being leftmost and 3 being rightmost slot
	* Return: Nothing
	*/
	void build_turret(std::string name_, int slot_);

	/*
	* Brief: Constructs a consumable
	* Param: The name of the consumable and what slot it goes into
	*	1 or 2, 1 being leftmost and 2 being rightmost slot
	* Return: Nothing
	*/
	void build_consumable(std::string name_, int slot);

	/*
	* Brief: Deletes the turret at the given slot
	* Param: Iterator of turret vector
	* Return: Nothing
	*/
	void delete_turret(int slot);

	/*
	* Brief: Deletes the consumable at the given slot
	* Param: Iterator of consumable vector
	* Return: Nothing
	*/
	void delete_consumable(int slot);

	/*
	* Brief: Getters for all the components of the floor
	* Param: Nothing
	* Return: Enemy vector reference, turret vector reference and
	*	consumable vector reference
	*/
	std::vector<Enemy>& getEnemies();
	std::vector<Turret>& getTurrets();
	std::vector<Consumable>& getConsumables();

};
