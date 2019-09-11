#pragma once

#include "stdafx.h"

/* Projectile is the bullets the are fired from Firearm
 * punch is the current hp of the Projectile
 * punch_ref is the max hp of the Projectile
 * damage is how much damage the Projectile will do
 *-------------------------------------------------------------
 * Note on punch
 * Punch works with an Enemy's thickness
 * Punch acts as the projectile's hp, where the projectile is dead if it reaches 0
 * Every enemy the projectile hits, the punch of the projectile will decrease by the enemy's thickness
 * Each enemy will take full damage regardless of current punch
 * If a projectile has 1 punch and an enemy has 1 thickness
 *		the projectile hits the enemy and does full damage, but does not continue on
 * If a projectile has 2 punch and an enemy has 1 thickness
 *		the projectile hits the enemy and does full damage, and continues on to hit the enemy behind it for full damage
 * If a projectile has 1 punch and an enemy has 2 thickness
 *		the projectile hits the enemy and does full damage, but does not continue on
 * For more information, see Enemy.h
 */

class Projectile : public Dynamic {
protected:
	int punch;
	int punch_ref;
	int damage;

public:

	/*
	* Brief: Basic constructor for projectile
	* Param: Name of projectile to be fired
	* Return: Nothing
	*/
	Projectile(std::string name_);

	/*
	* Brief: Constructor for upgraded projectile
	* Param: Name of projectile to be fired, level of projectile
	* Return: Nothing
	*/
	Projectile(std::string name_, int level);

	/*
	* Brief: Getter and setter for punch
	* Param: Nothing and punch value
	* Return: Current punch and nothing
	*/
	int getPunch();
	void setPunch(int newPunch);

	/*
	* Brief: Getter for a projectile's damage value
	* Param: Nothing
	* Return: Damage dealt by projectile
	*/
	int getDamage();

	/*
	* Brief: Activator for a projectile
	* Param: Player's right edge and center coordinates, floor number
	* Return: Nothing
	* Note: This is how a projectile is fired
	*/
	void setActive(int playerX, int playerC, int floor_);

	/*
	* Brief: Recycles used/dead projectiles for reuse
	* Param: Nothing
	* Return: Nothing
	* Note: Allows active and dead projectiles to be reused
	*		This heavily improves runtime performance as new projectiles
	*		do not need to be generated
	*/
	void revive();
};