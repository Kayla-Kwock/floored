#include "stdafx.h"


void calculate_projectile_interaction(
	Enemy& enemy,
	sf::RenderWindow& window,
	Projectile& projectile,
	float delta,
	int framebuffer) {
	window.draw(projectile.getSprite());
	projectile.moveRight(delta);
	if ((projectile.getXR() >= window.getSize().x || projectile.getPunch() < framebuffer) && projectile.isActive() && projectile.isNotDead()) {
		projectile.setDead();
	}
	else if (projectile.getPunch() <= 0 && projectile.isNotDead()) {
		projectile.setPunch(projectile.getPunch() - 1);
	}
	else if (projectile.getPunch() > 0 && projectile.getFloor() == enemy.getFloor() && enemy.isNotDead() && projectile.isActive()){
		PEcollision(projectile, enemy);
	}
}

void PEcollision(Projectile& projectile, Enemy& enemy) {
	if (projectile.getPunch() <= enemy.getThickness()) {
		projectile.setPunch(0);
	}
	else projectile.setPunch(projectile.getPunch() - enemy.getThickness());
	if (enemy.getHP() <= projectile.getDamage()) {
		enemy.setHP(0);
		enemy.setDead();
	}
	else enemy.setHP(enemy.getHP() - projectile.getDamage());
}

void CEcollision(Consumable& consumable, Enemy& enemy, float delta){
	if (consumable.isActive() && enemy.isNotDead()) {
		consumable.activate(enemy, delta);
	}
}
