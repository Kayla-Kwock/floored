#include "stdafx.h"

//Does all current frame calculations and updates object positions
bool newPositions(
	GameManager& gm,
	float delta) {
	int framebuffer = -20;
	bool already_dead = false;
	bool all_dead = true;

	// Handles the Cat Gun's sound effect
	NyanOffset = all_sfx[19].getPlayingOffset().asSeconds();
	if (!(sf::Mouse::isButtonPressed(sf::Mouse::Left)) || 
		!(gm.getPlayer().getEquipped().getName() == "Cat Gun")){//If no longer shooting Cat Gun
			all_sfx[19].pause();//Pause the SFX
	}

	//Begin frame calculations
	for (std::size_t i = 0; i < gm.getFloors().size(); i++) {//By Floor
		gm.getWindow().draw(gm.getFloors().at(i).get().getSprite());
		for (std::size_t j = 0; j < gm.getFloors().at(i).get().getEnemies().size(); j++) {//By enemy
			already_dead = gm.getFloors().at(i).get().getEnemies().at(j).isDead(); //Saves if the enemy is dead
			if (gm.getFloors().at(i).get().getEnemies().at(j).isNotDead()) {//If the enemy isn't dead
				gm.getFloors().at(i).get().getEnemies().at(j).moveLeft(delta);//Move the enemy left
			}
			for (std::size_t t = 0; t < gm.getFloors().at(i).get().getTurrets().size(); t++) {//By turret
				gm.getWindow().draw(gm.getFloors().at(i).get().getTurrets().at(t).getSprite());//Draw the turret
				gm.getFloors().at(i).get().getTurrets().at(t).shoot();//Attempt to shoot turret
				for (std::size_t x = 0; x < gm.getFloors().at(i).get().getTurrets().at(t).getFirearm().getAmmo().size(); x++) {//By bullet in a turret
					calculate_projectile_interaction(//Check if bullet interacts with enemy
						gm.getFloors().at(i).get().getEnemies().at(j), 
						gm.getWindow(),
						gm.getFloors().at(i).get().getTurrets().at(t).getFirearm().getAmmo().at(x), 
						delta, 
						framebuffer);
				}
			}//End Turret
			for (std::size_t c = 0; c < gm.getFloors().at(i).get().getConsumables().size(); c++) {//Begin Consumables
				gm.getWindow().draw(gm.getFloors().at(i).get().getConsumables().at(c).getSprite());//Draw consumables
				if ((gm.getFloors().at(i).get().getConsumables().at(c).getXR() >= gm.getFloors().at(i).get().getEnemies().at(j).getXL()) 
					&& gm.getFloors().at(i).get().getEnemies().at(j).getXL() >= 0) {//Check if the enemy should interact with consumable
					CEcollision(gm.getFloors().at(i).get().getConsumables().at(c), gm.getFloors().at(i).get().getEnemies().at(j), delta);
				}
			}//End Consumables
			for (std::size_t q = 0; q < gm.getPlayer().getEquipped().getAmmo().size(); q++) {//By bullet in equipped gun
				calculate_projectile_interaction(//Check if player's gun should interact with enemy
					gm.getFloors().at(i).get().getEnemies().at(j), 
					gm.getWindow(), 
					gm.getPlayer().getEquipped().getAmmo().at(q), 
					delta,
					framebuffer);
			}//End Equipped
			//For holstered weapon, this case exists so that if the player shoots and switches weapon
			//	the bullets will still interact as expected in the now holstered gun
			for (std::size_t m = 0; m < gm.getPlayer().getHolstered().getAmmo().size(); m++) {//By bullet in holstered gun
				calculate_projectile_interaction(//Check if player's holstered gun should interact with enemy
					gm.getFloors().at(i).get().getEnemies().at(j),
					gm.getWindow(), 
					gm.getPlayer().getHolstered().getAmmo().at(m), 
					delta,
					framebuffer);
			}//End Holstered
			if (!already_dead && gm.getFloors().at(i).get().getEnemies().at(j).isDead()) {//If the enemy was killed in this frame
				gm.getPlayer().setMoney(gm.getFloors().at(i).get().getEnemies().at(j).dropMoney());//Add the money to the player's total
			}
			if ((gm.getFloors().at(i).get().getEnemies().at(j).getXL() <= 100) &&
				gm.getFloors().at(i).get().getEnemies().at(j).isNotDead() &&
				gm.getFloors().at(i).get().getEnemies().at(j).isActive()) {//If the enemy reaches the shaft alive
				gm.getShaft().setHP(gm.getFloors().at(i).get().getEnemies().at(j).getDamage());//Deal damage to shaft
				if (gm.getShaft().dead()) {//If the shaft dies because of this
					gm.setGameOver(true);//Ya lose, nerd
				}
				else {//Else set the enemy at the edge of the shaft
					gm.getFloors().at(i).get().getEnemies().at(j).setX(100);
				}
			}
			if (gm.getFloors().at(i).get().getEnemies().at(j).isActive() && gm.getFloors().at(i).get().getEnemies().at(j).isNotDead()) {
				gm.getWindow().draw(gm.getFloors().at(i).get().getEnemies().at(j).getSprite());//Draw the enemy if it is not dead
			}
			all_dead = (gm.getFloors().at(i).get().getEnemies().at(j).isDead() && all_dead);//Checks if all enemies on floor is dead
		}//End Enemy
	}//End Floor
	//The above loop runs 5 times, once for each floor
	gm.getShaft().drawHP(gm.getWindow());//Draw the elevator shaft hp
	return all_dead;//If all enemies on all floors are dead, go to next round
}

//Simple algorithm to place an object on the floor
int place_on_floor(int floor_, int spHeight_) {
	//100 is floor height, floor_ is the floor of the object
	//	95 is 100-5, so floor height minus the thickness of the floor
	//	134 is the height of the letter-boxing of the game screen
	//	spHeight_ is the height of the sprite
	return (100 * (floor_ - 1) + 95 - spHeight_ + 134);
}