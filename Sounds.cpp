#include "stdafx.h"

void loadSounds(std::map<std::string, sf::SoundBuffer>& map) {
	for (std::size_t i = 0; i < 100; i++) {
		all_sfx.push_back(*new sf::Sound);
	}
	map["Peashooter"].loadFromFile("SFX/Peashooter.wav");
	map["Heavy Machine Gun"].loadFromFile("SFX/Heavy Machine Gun.wav");
	map["Tachanka"].loadFromFile("SFX/Heavy Machine Gun.wav");
	map["Railgun"].loadFromFile("SFX/Railgun.wav");
	map["Lazer Turret"].loadFromFile("SFX/Lazer Turret.wav");
	map["Pistol"].loadFromFile("SFX/Pistol.wav");
	map["Sniper"].loadFromFile("SFX/Sniper.wav");
	map["Cat Gun"].loadFromFile("SFX/Cat Gun.wav");
	map["Minigun"].loadFromFile("SFX/Minigun.wav");
	map["Needler"].loadFromFile("SFX/Needler.wav");
	map["Mine"].loadFromFile("SFX/Mine.wav");
	map["Gulper"].loadFromFile("SFX/Gulper.wav");
	all_sfx[19].setBuffer(map["Cat Gun"]);
	all_sfx[19].setLoop(true);
}

void playBGM() {
	sf::Music bgm;
	std::vector<int> songs;
	int song_number;
	int numSongs = 3;
	int currentSong;
	bool hasSong;
	srand(time(NULL));
	while (true) {
		if (songs.empty()) {
			for (std::size_t i = 1; i <= numSongs;) {
				hasSong = false;
				song_number = rand() % numSongs;
				for (std::size_t j = 0; j < songs.size(); j++) {
					if (songs[j] == song_number) {
						hasSong = true;
					}
				}
				if (!hasSong) {
					songs.push_back(song_number);
					i++;
				}
			}
		}
		if (bgm.getStatus() == sf::SoundSource::Status::Stopped) {
			currentSong = songs[0];
			songs.erase(songs.begin());
			switch (currentSong) {//Emilia is 60
			case(0):
				//bgm.openFromFile("BGM/Membrane.ogg");
				bgm.openFromFile("BGM/Emilia.ogg");
				//bgm.openFromFile("BGM/Reol.ogg");
				bgm.setVolume(60);
				break;
			case(1):
				//bgm.openFromFile("BGM/Reol.ogg");
				//bgm.openFromFile("BGM/Membrane.ogg");
				bgm.openFromFile("BGM/Emilia.ogg");
				bgm.setVolume(60);
				break;
			case(2):
				bgm.openFromFile("BGM/Emilia.ogg");
				//bgm.openFromFile("BGM/Reol.ogg");
				//bgm.openFromFile("BGM/Membrane.ogg");
				bgm.setVolume(60);
			}
			bgm.play();
		}
	}
}

void playSFX(std::string name) {
	for (std::size_t i = 0; i < all_sfx.size(); i++) {
		if (all_sfx[i].getStatus() == sf::SoundSource::Stopped) {
			if (name == "Cat Gun") {
				if (all_sfx[19].getStatus() == sf::SoundSource::Stopped || all_sfx[19].getStatus() == sf::SoundSource::Paused) {
					all_sfx[19].setPlayingOffset(sf::seconds(NyanOffset));
					all_sfx[19].setVolume(75);
					all_sfx[19].play();
				}
			}
			else {
				all_sfx[i].setBuffer(all_sounds[name]);
			}
			if (name == "Lazer Turret") {
				all_sfx[i].setVolume(60);
			}
			else if (name == "Peashooter" || name == "Tachanka") {
				all_sfx[i].setVolume(30);
			}
			else if (name == "Railgun") {
				all_sfx[i].setVolume(60);
			}
			else if (name == "Mine") {
				all_sfx[i].setVolume(100);
			}
			else
				all_sfx[i].setVolume(50);
			all_sfx[i].play();
			break;
		}
	}
}
