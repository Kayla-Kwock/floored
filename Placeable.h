#pragma once
#include "stdafx.h"

/* Placeable is a parent class for Turrets and Consumables
 * cost is how much it takes to build the placeable
 * slot_num represents which slot the placeable occupies
 * floor is which floor the placeable is on
 * name is the name of the placeable
 * upgradeInfo is described in Upgrade.h
 * level is the level of the placeable
 */
class Placeable: public Object {
	protected:
		int cost;
		int slot_num;
		int floor;
		std::string name;
		struct upgradeInfo;
		int level;
	public:

		/*
		* Brief: Getter for the slot of the placeable
		* Param: Nothing
		* Return: The slot number the placeable occupies
		*/
		int getSlot();

		/*
		* Brief: Virtual function for the different upgrades of turrets and consumables
		* Param: Nothing
		* Return: Nothing
		* Note: Consumables both repair and level up while turrets only level up
		*/
		virtual void upgrade();

		/*
		* Brief: Getter for name
		* Param: Nothing
		* Return: The name of the placeable
		*/
		std::string getName();

		/*
		* Brief: Getter for level
		* Param: Nothing
		* Return: The level of the placeable
		*/
		int getLevel();
};