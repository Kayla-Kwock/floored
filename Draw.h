#pragma once

#include "stdafx.h"

/*
* Brief: Calculates and draws the result of a frame tick
* Param: GameManager reference and a frame time
* Return: If all the enemies have been killed
* Note: This function is the game. Everything during the game phase happens in this function
*/
bool newPositions(
	GameManager& gm,
	float delta);

/*
* Brief: Calculates the Y-Coordinate of a sprite so that it appears to rest on the floor
* Param: Floor number and a sprite height
* Return: The height in which a sprite should be placed to appear to contact the floor
*/
int place_on_floor(int floor_, int spHeight_);