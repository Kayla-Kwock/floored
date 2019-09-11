#pragma once

#include "stdafx.h"

/* Enemies are the multiple opponents you face in the game
 * hp is how much damage the enemy can take before dying
 * thickness is how much damage the enemy does to projectiles
 * damage is how much damage the enemy does to the elevator
 * xscale and yscale are the scaling factors to resize the sprites
 * money is how much money is dropped by the enemy upon death
 *--------------------------------------------------------------------
 * Note on thickness
 * This value is used with a Projectile's punch value.
 * Thickness acts as how much damage it will do to a projectile
 * The projectile's punch is it's hp
 * Regardless of the projectile's punch, the enemy will take full damage
 * If a projectile's punch reaches 0 after hitting an enemy, it is dead
 * If a projectile's punch is more than 0 after hitting an enemy, it will hit the enemy behind
 * For more information, see Projectile.h
 */

class Enemy : public Dynamic {
protected:
	int hp;
	int thickness;
	int damage;
	float xscale = 1;
	float yscale = 1;
	int money;

public:

	/*
	* Brief: Constructor for an enemy
	* Param: The floor to be spawned on and the type of enemy to spawn
	* Return: Nothing
	*/
	Enemy(int floor_, std::string name_);

	/*
	* Brief: Activates the enemy
	* Param: A RenderWindow to spawn the enemy
	* Return: Nothing
	* Note: Does not create new enemies, instead activates preloaded enemies
	* Improves runtime performance
	*/
	void setActive(sf::RenderWindow& window);

	/*
	* Brief: Getter and Setter for HP
	* Param: Nothing and a new HP
	* Return: Enemy's current HP and nothing
	*/
	int getHP();
	void setHP(int newHP);

	/*
	* Brief: Getter for an enemy's thickness
	* Param: Nothing
	* Return: The enemy's thickness
	*/
	int getThickness();

	/*
	* Brief: Getter for an enemy's damage
	* Param: Nothing
	* Return: How much damage the enemy does per hit
	*/
	int getDamage();

	/*
	* Brief: Getter for how much money an enemy drops on death
	* Param: Nothing
	* Return: Amount of money to be dropped
	*/
	int dropMoney();
};