#include "stdafx.h"

//Constructor for a clean Firearm
Firearm::Firearm(std::string name_) {
	//Fills out the stats of the firearm and fills up the
	//	ammo reserves with the correct projectile
	level = 1;
	stats info = getStats(name_);
	ROF = info.ROF;
	name = name_;
	for (std::size_t i = 0; i < info.ammo_count; i++) {
		ammo.push_back(*new Projectile(name_));
	}
}

//Constructor for an upgraded Firearm
Firearm::Firearm(std::string name_, int level) {
	//Fills out the stats of the firearm and fills up the
	//	ammo reserves with the correct projectile
	this->level = level;
	name = name_;
	stats upgradeInfo = getUpgrade(name_, level);
	ROF = upgradeInfo.ROF;
	for (std::size_t i = 0; i < upgradeInfo.ammo_count; i++) {
		ammo.push_back(*new Projectile(name_, level));
	}
}

//Shoots the firearm
void Firearm::shoot(int XR, int YD, int texture_height, int floor_) {
	//If it has been a sufficent amount of time, based on the Firearm's ROF
	//	since the last bullet has been shot, fire another one
	time = clock.getElapsedTime();
	if (time.asSeconds() >= 1/(ROF/ 60)){;
		for (std::size_t i = 0; i < ammo.size(); i++) {
			//Revives all ammo that is no longer in play, allowing it to be
			//	reused
			if (this->ammo[i].isActive() && this->ammo[i].isDead()) {
				this->ammo[i].revive();
			}
			//If the ammo is ready to be shot, fire it from the player's center
			else if (!(this->ammo[i].isActive())) {
				ammo[i].setActive(XR, YD - texture_height / 2, floor_);
				playSFX(name);//Play sound effect of Firearm
				break;
			}
		}
		clock.restart();//Reset the time since last bullet shot
	}
}

//Refreshes the ammo inside a Firearm between waves
//	correctly applies stats of the Firearm based on level
void Firearm::reload() {
	ammo.erase(ammo.begin(), ammo.end());
	stats upgradeInfo = getUpgrade(name, level);
	for (std::size_t i = 0; i < upgradeInfo.ammo_count; i++) {
		ammo.push_back(*new Projectile(name, level));
	}
}

//Upgrades the Firearm's level
//	Does not actually change the stats of the projectile
//	this is done in reload
void Firearm::upgrade() {
	level++;
}

//Getter for a reference to the Firearm's ammo vector
std::vector<Projectile>& Firearm::getAmmo() {
	std::vector<Projectile>& ref = this->ammo;
	return ref;
}

//Getter and setter for a Firearm's level
int Firearm::getLevel() {
	return level;
}

void Firearm::setLevel(int level_) {
	level = level_;
}

//Getter for the name of the Firearm
std::string Firearm::getName() {
	return name;
}

