#pragma once

#include "stdafx.h"

/*
 * Brief: Loads all the sounds into a map
 * Param: A map reference
 * Return: Nothing
 * Note: Runs only in initialization
 */
void loadSounds(std::map<std::string, sf::SoundBuffer>& map);

/*
 * Brief: Runs the background music
 * Param: Nothing
 * Return: Nothing
 */
void playBGM();


/*
 * Brief: Plays a selected sound effect
 * Param: Name of desired sound effect
 * Return: Nothing
 */
void playSFX(std::string name);
