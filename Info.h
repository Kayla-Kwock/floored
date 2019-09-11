#pragma once

#include "stdafx.h"

/* Holds all the base information of everything
 * Enemy, Firearm, and Consumable stats are all stored in getStats
 * struct stats provides an easy way for anything to obtain all the necessary components
 *		from getStats regardless of end goal
 *------------------------------------------------------
 * Quick Description
 *	Cost - How much money the object costs to buy
 *	Damage - How much damage the object will do on attack
 *	hp - How much HP the object has
 *	ROF - How fast the object can fire its Projectiles
 *	Punch - How durable the Projectile is
 *	ammo_count - How much ammo is in the Firearm
 *		Faster firing weapons have more ammo
 *	bullet_speed - How fast will the Projectile travel across the screen
 *	enemy_speed - How fast will the Enemy travel across the screen
 *	thickness - How thick an Enemy is
 *		Higher thickness will reduce the punch of a Projectile more
 *	money - How much money will an Enemy drop on death
 */

struct stats {
	int cost;
	int damage;
	int hp;
	int ROF;
	int punch;
	int ammo_count;
	int bullet_speed;
	int enemy_speed;
	int thickness;
	int money;
	stats(): cost(0), damage(0), hp(0), ROF(0), punch(0), ammo_count(0), bullet_speed(0), enemy_speed(0), thickness(0), money(0){};
};

stats getStats(std::string name);