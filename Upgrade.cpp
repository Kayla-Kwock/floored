#include "stdafx.h"

stats getUpgrade(std::string name, int level) {
	double cLevel = level - 1;//Current level
	stats upgradedInfo;
	stats info = getStats(name);
	if (name == "Peashooter") {
		upgradedInfo.damage = info.damage + (info.damage * (cLevel) * 0.75);
		upgradedInfo.punch = info.punch + (cLevel);
		upgradedInfo.cost = info.cost + ((cLevel) * 100);
		upgradedInfo.bullet_speed = info.bullet_speed;
		upgradedInfo.ammo_count = info.ammo_count;
	}
	else if (name == "Heavy Machine Gun") {
		upgradedInfo.damage = info.damage + (20 * cLevel);
		upgradedInfo.punch = info.punch + (floor(cLevel * 0.5));
		upgradedInfo.cost = info.cost + (cLevel * 100);
		upgradedInfo.bullet_speed = info.bullet_speed;
		upgradedInfo.ammo_count = info.ammo_count;
	}
	else if (name == "Tachanka") {
		upgradedInfo.damage = info.damage + (cLevel * 25);
		upgradedInfo.punch = info.punch;
		upgradedInfo.cost = info.cost + (cLevel * 100);
		upgradedInfo.bullet_speed = info.bullet_speed;
		upgradedInfo.ammo_count = info.ammo_count;
	}
	else if (name == "Railgun") {
		upgradedInfo.damage = info.damage + (cLevel * 30);
		upgradedInfo.punch = info.punch + cLevel;
		upgradedInfo.cost = info.cost + (cLevel * 100);
		upgradedInfo.bullet_speed = info.bullet_speed;
		upgradedInfo.ammo_count = info.ammo_count;
	}
	else if (name == "Lazer Turret") {
		upgradedInfo.damage = info.damage + (cLevel * 10);
		upgradedInfo.punch = info.punch;
		upgradedInfo.cost = info.cost + (cLevel * 100);
		upgradedInfo.bullet_speed = info.bullet_speed;
		upgradedInfo.ammo_count = info.ammo_count;
	}
	else if (name == "Pistol") {
		upgradedInfo.damage = info.damage + (info.damage * (cLevel * 0.5));
		upgradedInfo.punch = info.punch + (floor(cLevel*0.5));
		upgradedInfo.cost = info.cost + 2 * (cLevel * 100);
		upgradedInfo.bullet_speed = info.bullet_speed;
		upgradedInfo.ammo_count = info.ammo_count;
	}
	else if (name == "Sniper") {
		upgradedInfo.damage = info.damage + (info.damage * cLevel/2);
		upgradedInfo.punch = info.punch + cLevel + floor(cLevel * 0.5);
		upgradedInfo.cost = info.cost + (cLevel * 50);
		upgradedInfo.bullet_speed = info.bullet_speed;
		upgradedInfo.ammo_count = info.ammo_count;
	}
	else if (name == "Cat Gun") {
		upgradedInfo.damage = info.damage + (10 * cLevel);
		upgradedInfo.punch = info.punch + (2 * cLevel);
		upgradedInfo.cost = info.cost + (cLevel * 100);
		upgradedInfo.bullet_speed = info.bullet_speed;
		upgradedInfo.ammo_count = info.ammo_count;
	}
	else if (name == "Minigun") {
		upgradedInfo.damage = info.damage + (cLevel * 20);
		upgradedInfo.punch = info.punch + (cLevel);
		upgradedInfo.cost = info.cost + (-pow(0.5,level) * info.cost);
		upgradedInfo.bullet_speed = info.bullet_speed;
		upgradedInfo.ammo_count = info.ammo_count;
	}
	else if (name == "Needler") {
		upgradedInfo.damage = info.damage + (cLevel * 20);
		upgradedInfo.punch = info.punch + (floor(cLevel * 0.25));
		upgradedInfo.cost = info.cost + (cLevel * 75);
		upgradedInfo.bullet_speed = info.bullet_speed;
		upgradedInfo.ammo_count = info.ammo_count;
	}
	else if (name == "Mine"){
		upgradedInfo.damage = info.damage + (10 * cLevel*(cLevel));
		upgradedInfo.cost = info.cost + (50 * cLevel);
	}
	else if (name == "Wall") {
		upgradedInfo.hp = info.hp + (2000 * cLevel);
		upgradedInfo.cost = info.cost + 100 * cLevel;
	}
	else if (name == "Bandit Wire") {
		upgradedInfo.damage = info.damage + (pow(cLevel,2));
		upgradedInfo.cost = info.cost + (50 * cLevel);
	}
	else if (name == "Buzzsaw") {
		upgradedInfo.damage = info.damage + (info.damage * (0.25 * cLevel));
		upgradedInfo.hp = info.hp + (500 * cLevel);
		upgradedInfo.cost = info.cost + 200 * cLevel;
	}
	else if (name == "Gulper") {
		upgradedInfo.damage = info.damage;
		upgradedInfo.cost = info.cost;
	}
	upgradedInfo.ROF = info.ROF;
	return upgradedInfo;
}