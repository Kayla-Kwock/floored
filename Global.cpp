#include "stdafx.h"

//See Global.h for comments
std::map<std::string, sf::SoundBuffer>& all_sounds = *new std::map<std::string, sf::SoundBuffer>;

std::vector<sf::Sound> all_sfx = *new std::vector<sf::Sound>;

float NyanOffset = 0;

Turret turret_master = *new Turret();

Consumable consumable_master = *new Consumable();