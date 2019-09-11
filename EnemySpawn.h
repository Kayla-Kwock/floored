#pragma once
#include "stdafx.h"

/*
* Brief: Creates new enemies for a specific floor
* Param: Vector reference for enemies, floor number, and wave multiplier
* Return: Nothing
*/
void create_wave(std::vector<Enemy>& enemies, int floor_, double multiplier);

/*
* Brief: Creates new enemies for the next wave
* Param: Vector reference for all the floors, current wave
* Return: Nothing
*/
void create_set(std::vector<std::reference_wrapper<Floor>>& floors, int wave);

/*
* Brief: Spawns the enemies into the game field
* Param: RenderWindow reference, vector reference for all the floors
* Return: Nothing
* 
*/
void spawn(sf::RenderWindow& window, std::vector<std::reference_wrapper<Floor>>& floors);