#pragma once

#include "stdafx.h"

/* Shaft is what the player needs to protect
 * max_hp and current_hp saves the hp of the shaft
 * current_hp is set to max_hp at the start of every round
 */

class Shaft : public Object {
protected:
	double max_hp = 10000;
	double current_hp = max_hp;
public:

	/*
	* Brief: Constructor
	* Param: Nothing
	* Return: Nothing
	*/
	Shaft();

	/*
	* Brief: Getters and setters for current_hp
	* Param: Nothing, damage to be done and nothing
	* Return: Current_hp, nothing and nothing
	* Note: setHP is used when enemies hit the elevator shaft
	*		resetHP is used at the beginning of every round
	*/
	int getHP();
	void setHP(int damage);
	void resetHP();

	/*
	* Brief: Checks if the elevator is dead
	* Param: Nothing
	* Return: True if the current_hp <= 0, false otherwise
	*/
	bool dead();

	/*
	* Brief: Draws the hp bar on screen
	* Param: Reference to display window
	* Return: Nothing
	*/
	void drawHP(sf::RenderWindow& window);
};

