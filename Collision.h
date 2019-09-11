#pragma once

#include "stdafx.h"

/*
* Brief: Calculates the next state for a projectile (destroyed, enemy contact, keep moving) and draws it to the display
* Param: Enemy reference, a RenderWindow reference, Projectile reference, time between frames, number of frames a projectile is to be shown
* Return: Nothing
*/
void calculate_projectile_interaction(
	Enemy& enemy,
	sf::RenderWindow& window,
	Projectile& projectile,
	float delta,
	int framebuffer);

/*
* Brief: Calculates the result of a projectile and an enemy colliding with one another
* Param: A projectile reference and an enemy reference
* Return: Nothing
*/
void PEcollision(Projectile& projectile, Enemy& enemy);


/*
* Brief: Calculates the result of a consumable and an enemy interacting
* Param: A consumable reference and enemy reference
* Return: Nothing
*/
void CEcollision(Consumable& consumable, Enemy& enemy, float delta);