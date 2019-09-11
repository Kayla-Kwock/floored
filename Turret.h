#pragma once

#include "stdafx.h"

/* Turret is a placeable object that fires at the enemies to assist the player
 * firearm is the Firearm that holds the turret's stats
 * position it the turret's slot on a floor's turret vector
 */
class Turret : public Placeable {
protected:
	Firearm firearm;
	int position;
public:

	/*
	* Brief: Default constructor
	* Param: None
	* Return: None
	*/
	Turret();

	/*
	* Brief: Basic constructor 
	* Param: Name of turret, floor number, slot number
	* Return: Nothing
	*/
	Turret(std::string name_, int floor_, int slot_);

	/*
	* Brief: Getter for the turret's level (inherited from placeable)
	* Param: Nothing
	* Return: Turret's level
	*/
	int getLevel();

	/*
	* Brief: Getter for the turret's firearm
	* Param: Nothing
	* Return: The turret's Firearm
	*/
	Firearm& getFirearm();

	/*
	* Brief: Fires the turret's Firearm
	* Param: Nothing
	* Return: Nothing
	* Note: Simply calls the firearm's shoot function
	*/
	void shoot();

	/*
	* Brief: Upgrades the turret
	* Param: Nothing
	* Return: Nothing
	* Note: Increments the turret and the firearm's level
	*/
	void upgrade() override;
};

