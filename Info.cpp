#include "stdafx.h"

//This function holds all the information for every dynamic object
//	in the game! Well, at least base stats. The upgraded stats are 
//	handled by Upgrade.cpp
//All the function needs is a name of a dynamic object and it will
//	return all the relevant information about the object in a nice,
//	clean package in a strcut that is easy to extract the data from
stats getStats(std::string name) {
	stats info;
	//Begin Turrets
	if (name == "Peashooter") {
		info.damage = 15;
		info.punch = 1;
		info.bullet_speed = 2000;
		info.cost = 50;
		info.ROF = 60;
		info.ammo_count = 5;
	}
	else if (name == "Heavy Machine Gun") {
		info.damage = 40;
		info.punch = 2;
		info.bullet_speed = 2000;
		info.cost = 225;
		info.ROF = 45;
		info.ammo_count = 5;
	}
	else if (name == "Tachanka") {
		info.damage = 30;
		info.punch = 1;
		info.bullet_speed = 2000;
		info.cost = 150;
		info.ROF = 100;
		info.ammo_count = 5;
	}
	else if (name == "Railgun") {
		info.damage = 100;
		info.punch = 5;
		info.bullet_speed = 2000;
		info.cost = 250;
		info.ROF = 15;
		info.ammo_count = 5;
	}
	else if (name == "Lazer Turret") {
		info.damage = 60;
		info.punch = 10;
		info.bullet_speed = 1000;
		info.cost = 400;
		info.ROF = 10;
		info.ammo_count = 5;
	}//End Turrets
	//Begin Player Guns
	else if (name == "Pistol") {
		info.damage = 20;
		info.punch = 1;
		info.bullet_speed = 2000;
		info.cost = 0;
		info.ROF = 200;
		info.ammo_count = 5;
	}
	else if (name == "Sniper") {
		info.damage = 40;
		info.punch = 3;
		info.bullet_speed = 1000;
		info.cost = 500;
		info.ROF = 60;
		info.ammo_count = 5;
	}
	else if (name == "Cat Gun") {
		info.damage = 50;
		info.punch = 2;
		info.bullet_speed = 750;
		info.cost = 1000;
		info.ROF = 220;
		info.ammo_count = 5;
	}
	else if (name == "Minigun") {
		info.damage = 30;
		info.punch = 2;
		info.bullet_speed = 1000;
		info.cost = 2000;
		info.ROF = 500;
		info.ammo_count = 7;
	}
	else if (name == "Needler") {
		info.damage = 20;
		info.punch = 4;
		info.bullet_speed = 1500;
		info.cost = 500;
		info.ROF = 200;
		info.ammo_count = 6;
	}//End Player Guns
	//Begin Consumables
	else if (name == "Mine") {
		info.damage = 100;
		info.cost = 50;
	}
	else if (name == "Wall") {
		info.hp = 600;
		info.cost = 200;
	}
	else if (name == "Bandit Wire") {
		info.damage = 1;
		info.cost = 400;
	}
	else if (name == "Buzzsaw") {
		info.damage = 10;
		info.cost = 500;
		info.hp = 500;
	}
	else if (name == "Gulper") {
		info.damage = 9999;
		info.cost = 1000;
	}//End Consumables
	//Start Enemies
	else if (name == "Ghost"){
		info.hp = 120;
		info.thickness = 1;
		info.damage = 1;
		info.enemy_speed = 100;
		info.money = 20;
	}
	else if (name == "Hunter") {
		info.hp = 75;
		info.thickness = 1;
		info.damage = 3;
		info.enemy_speed = 225;
		info.money = 25;
	}
	else if (name == "Harpy") {
		info.hp = 300;
		info.thickness = 2;
		info.damage = 3;
		info.enemy_speed = 125;
		info.money = 50;
	}
	else if (name == "Tank") {
		info.hp = 500;
		info.thickness = 2;
		info.damage = 3;
		info.enemy_speed = 50;
		info.money = 75;
	}
	else if (name == "Wizard") {
		info.hp = 750;
		info.thickness = 5;
		info.damage = 5;
		info.enemy_speed = 150;
		info.money = 300;
	}
	return info;
}