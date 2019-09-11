#pragma once

#include "stdafx.h"
/* A Consumable is a player-deployed defense that interacts with enemies in other ways besides shooting
 * interaction_type is a tag that says how the consumable interacts with the enemies
 *		mines damage the enemy, therefore they have the damage tag and walls block the enemy so the have the block tag
 * usage is a tag that says how many times the consumable can be triggered without needing to be repaired
 *		mines are one-time use, so the tag is once while walls are many-time use, so the tag is many
 * max_hp is used for consumables with a usage of many. It saves the maximum hp, and tells how much hp can be repaired
 * current_hp is used for consumables with a usage of many. It saves the current hp, and is how much damage it can take
 * damage is used for consumables with a interaction_type of damage and damage/block. It reports how much damage the 
 *		the consumable does upon activation
 * active tells if the consumable can be activated. If true, then enemies will interact, else they will ignore it
 * dead_texture is the texture of the consumable when it has been activated/destroyed. Upon destruction, the texture
 *		of the consumable will swap to this texture until repaired
 */
class Consumable : public Placeable {
	protected:
		std::string interaction_type;//Tells what kind of effect the consumable will have (damage, wall, etc)
		/*types are damage, block, damage/block*/
		std::string usage;//Tells how many times the consumable can be used (mines can only be used once for example)
		/*Usage options can be once or many*/
		int max_hp;
		int current_hp;
		int damage;
		bool active;
		sf::Texture dead_texture;
	public:

		/*
		* Brief: Default constructor
		* Param: Nothing
		* Return: Nothing
		*/
		Consumable();

		/*
		* Brief: Basic constructor
		* Param: Name of consumable, floor to spawn on, slot to occupy
		* Return: Nothing
		*/
		Consumable(std::string name_, int floor_, int slot);

		/*
		* Brief: Triggers the consumable's effect (damage, block, damage/block)
		* Param: Enemy reference, frame time
		* Return: Nothing
		* Note: delta is used by anything with block by making
		*		the sprite move to the right before moving back left, effectively stopping the sprite
		*/
		void activate(Enemy& enemy, float delta);

		/*
		* Brief: Resets the consumable
		* Param: Nothing
		* Return: Nothing
		*/
		void reload();

		/*
		* Brief: Upgradeds the consumable
		* Param: Nothing
		* Return: Nothing
		* Note: Increments the level (inherited from Placeable) and repairs
		*/
		void upgrade() override;

		/*
		* Brief: Getter for active
		* Param: Nothing
		* Return: The variable active
		*/
		bool isActive();

		/*
		* Brief: Setter for the hp
		* Param: Damage taken
		* Return: Nothing
		* Note: Used by anything with block
		*/
		void setHP(int damage);
};