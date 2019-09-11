#include "stdafx.h"

int main()
{
	srand(time(NULL));
	loadSounds(all_sounds);
	sf::Thread bgm(&playBGM);
	bgm.launch();
	std::vector<Floor> construct;
	for (std::size_t i = 1; i <= 5; i++) {
		construct.push_back(*new Floor(i));
	}
	GameManager gm(*new std::vector<std::reference_wrapper<Floor>>(construct.begin(), construct.end()));
	gm.initialize();
	for (std::size_t i = 1; i <= 15; i++) {
		gm.setWave(i);
		gm.phaseUpgrade();
		gm.phaseLoading(i);
		if (gm.phaseGame()) {
			//Lost screen goes here
			break;
		}
	}
	return 0;
}