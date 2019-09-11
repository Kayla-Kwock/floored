#pragma once

#include "stdafx.h"

/*
 * Brief: Gets the stats of an item based on its level
 * Param: Name of item, level of item to search up
 * Return: stats struct (see Info.h for definition)
 * Note: Function stores all the upgrade algorithms for Firearms, Turrets and Consumables
 */
stats getUpgrade(std::string name, int current_level);