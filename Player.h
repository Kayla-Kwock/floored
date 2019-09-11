#pragma once

#include "stdafx.h"

/* Player is the playable character
 * equipped and holstered are the two Firearms the player will bring into battle
 * money is how much money the player has
 */
class Player : public Dynamic {
protected:
	std::reference_wrapper<Firearm> equipped = *new Firearm("Pistol", 1);
	std::reference_wrapper<Firearm> holstered = *new Firearm("Pistol", 1);
	int money = 500;
public:

	/*
	* Brief: Constructor
	* Param: Nothing
	* Return: Nothing
	*/
	Player();

	/*
	* Brief: Switches the equipped and holstered weapons
	* Param: Nothing
	* Return: Nothing
	* Note: Simply has the equipped weapon and the holstered weapon swap slots
	*/
	void switch_weapons();

	/*
	* Brief: Swaps the currently equipped weapons for other ones during upgrade phase
	* Param: The Firearm to switch with
	* Return: Nothing
	* Note: Used only in the upgrade phase when the player equips a different weapon
	*/
	void swap_equipped(Firearm& firearm);
	void swap_holstered(Firearm& firearm);

	/*
	* Brief: Fires the equipped Firearm
	* Param: Nothing
	* Return: Nothing
	*/
	void shoot_equipped();

	/*
	* Brief: Getters for the currently equipped Firearms
	* Param: Nothing
	* Return: Firearm reference
	*/
	Firearm& getEquipped();
	Firearm& getHolstered();

	/*
	* Brief: Getters and setters for player money
	* Param: Nothing and quantity of money
	* Return: Current money and nothing
	* Note: setMoney both adds and subtracts from the player count
	*		To subtract (when buying things for example), we pass a negative integer
	*		To add (when killing enemies), we pass a positive integer
	*/
	int getMoney();
	void setMoney(int money_);
};