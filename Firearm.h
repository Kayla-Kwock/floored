#pragma once

#include "stdafx.h"

/* Firearm is responsible for shooting a Projectile
 * clock and time are the internal clock of the weapon. 
 *		It keeps how long it has been since it has last fired
 * ROF (Rate of Fire) represents how fast the gun fires. Measured in Rounds per Minute.
 * ammo is every Projectile inside the firearm. When the gun fires, 
 *		it activates one of the Projectiles inside ammo
 * level is the current level of the firearm
 * name is the name of the firearm
 */
class Firearm: public Object {
protected:
	sf::Clock clock;
	sf::Time time;
	double ROF;
	std::vector<Projectile> ammo;
	int level;
	std::string name;
public:

	/*
	* Brief: Basic constructor for a Firearm
	* Param: Nothing
	* Return: Nothing
	* Note: Used only to create a reference for the Firearm in Global
	*/
	Firearm() {};

	/*
	* Brief: Constructor for a Firearm
	* Param: The type of firearm to create
	* Return: Nothing
	*/
	Firearm(std::string name_);

	/*
	* Brief: Constructor for a Firearm of a specific level
	* Param: The type of firearm to create, the level
	* Return: Nothin
	*/
	Firearm(std::string name_, int level);

	/*
	* Brief: Fires a Projectile from the Firearm
	* Param: Parameters to determine firing location
	* Return: Nothing
	*/
	void shoot(int XR, int YD, int texture_height, int floor_);

	/*
	* Brief: Updates the ammo inside the firearm
	* Param: Nothing
	* Return: Nothing
	* Note: Used during the loading phase, this is used to update the Projectiles
	*	so that their stats (damage, punch) are accurate to the new upgraded state
	*/
	void reload();

	/*
	* Brief: Upgrades the Firearm by increasing its level
	* Param: Nothing
	* Return: Nothing
	* Note: Used by all Player-wielded Firearms
	*/
	void upgrade();

	/*
	* Brief: Gets a reference to the ammo of a firearm
	* Param: Nothing
	* Return: A reference to the firearm's ammo
	*/
	std::vector<Projectile>& getAmmo();

	/*
	* Brief: Getters and setters for the Firearm's level
	* Param: Nothing and a new level
	* Return: Current level and nothing
	* Note: setLevel is used by turrets so the turret can update its Firearm to a new level
	*/
	int getLevel();
	void setLevel(int level_);

	/*
	* Brief: Getter for the name of the Firearm
	* Param: Nothing
	* Return: The name of the Firearm
	*/
	std::string getName();

};