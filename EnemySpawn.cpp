#include "stdafx.h"

//Fills a floor's enemy vector with a single type of enemy
void create_wave(std::vector<Enemy>& enemies, int floor_, double multiplier) {
	//Multiplier essentially means "Wave Number"
	double type;//Used to determine the type of enemy
	double quantity;//Used to determine how many enemies to spawn
	
	enemies.clear();//Empty the vector to clear last wave's enemies

	//Type determines what kind of enemy to spawn
	//	Is run so that every 3 waves, a new enemy type can be selected
	type = (rand() % int(ceil(multiplier / 3))) + 1;

	//Quantity decides how many to spawn by looking at the type of enemy
	//	and the current wave plus an extra 0-2 enemies.
	quantity = ceil(multiplier / type) + (rand()%3);

	//Fill the enemy vector using determined quantities
	for (std::size_t i = 0; i < quantity; i++) {
		switch (int(type)) {
		case(1):
			enemies.push_back(*new Enemy(floor_, "Ghost"));
			break;
		case(2):
			enemies.push_back(*new Enemy(floor_, "Hunter"));
			break;
		case(3):
			enemies.push_back(*new Enemy(floor_, "Harpy"));
			break;
		case(4):
			enemies.push_back(*new Enemy(floor_, "Tank"));
			break;
		case(5):
			enemies.push_back(*new Enemy(floor_, "Wizard"));
		}
	}
}

//Unified function to create all the enemies for a particular wave
void create_set(std::vector<std::reference_wrapper<Floor>>& floors,	int wave){
	for (std::size_t i = 0; i < floors.size(); i++) {
		create_wave(floors[i].get().getEnemies(), i + 1, wave);
	}
}

//Places the enemy into the game, is now able to interact with player and game field
void spawn(sf::RenderWindow& window, std::vector<std::reference_wrapper<Floor>>& floors) {
	for (std::size_t i = 0; i < floors.size(); i++) {// Activate one enemy on each floor
		for (std::size_t j = 0; j < floors[i].get().getEnemies().size(); j++) {
			if (!floors[i].get().getEnemies().at(j).isActive()) {//spawn the first available enemy on a particular floor
				floors[i].get().getEnemies().at(j).setActive(window);
				break;
			}
		}
	}//Go to the next floor
}
