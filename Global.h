#pragma once

#include "stdafx.h"

/* These are all variables that are globablly referrable
 * Since sf::SoundBuffer need to be initialized in main, it would have
 *		required a lot of re-organization of code to not have to use globals
 * Same thing for sf::Sound
 * Nyanoffset saves the current position in the sound effect for the Cat Gun
 * turret_master and consumable_master are empty shells for the turret/consumable clickables
 *		to reference as they need to be brace initialized as references
 */
extern std::map<std::string, sf::SoundBuffer>& all_sounds;

extern std::vector<sf::Sound> all_sfx;

extern float NyanOffset;

extern Turret turret_master;

extern Consumable consumable_master;