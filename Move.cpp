#include "stdafx.h"

void newPositions(
	sf::RenderWindow& window,
	std::vector<Projectile>& projectiles,
	std::vector<Enemy>& enemies,
	float delta)
{
	for (int i = 0; i < projectiles.size(); i++) {
		projectiles[i].moveRight(delta);
		if ((projectiles[i].getXL() >= window.getSize().x) || (projectiles[i].getPunch() == -99)) {
			projectiles.erase(projectiles.begin() + i);
			i--;
		}
		else for (int j = 0; j < enemies.size(); j++) {
			if (projectiles[i].getFloor() == enemies[j].getFloor()) {
				if (projectiles[i].getPunch() <= 0) {//If bullet has no more punch (stopped by enemy)
					break;//Stop comparing it to the enemies as the bullet is "dead"
				}
				if (projectiles[i].getPunch() <= enemies[j].getThickness()) {
					projectiles[i].setPunch(0);
				}
				else projectiles[i].setPunch(projectiles[i].getPunch() - enemies[j].getThickness());
				if (enemies[j].getHP() <= projectiles[i].getDamage()) {
					enemies.erase(enemies.begin() + j);
					j--;
				}
				else enemies[j].setHP(enemies[j].getHP() - projectiles[i].getDamage());
			}
		}
	}	
	projectiles.shrink_to_fit();
	enemies.shrink_to_fit();
	for (int j = 0; j < enemies.size(); j++) {
		if (enemies[j].getXL() <= 200) {
			//damage elevator
		}
		else enemies[j].moveLeft(delta);
	}
}
	
void drawful(sf::RenderWindow& window,
	std::vector<Projectile>& projectiles,
	std::vector<Enemy>& enemies) {
	for (int i = 0; i < projectiles.size(); i++) {
		window.draw(projectiles[i].getSprite());
		if (projectiles[i].getPunch() >= -15) {
			projectiles[i].setPunch(projectiles[i].getPunch() - 1);
		}
		else projectiles[i].setPunch(-99);
	}
	for (int j = 0; j < enemies.size(); j++) {
		window.draw(enemies[j].getSprite());
	}
}