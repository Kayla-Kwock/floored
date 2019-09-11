#pragma once

#include "stdafx.h"


/* struct clicked is used as a return value to represent which clickable was clicked on
* clicked_vector is the vector in which the clickable is saved
* iterator is the cell that the clicked clickable is saved
*/
struct clicked {
	std::vector<std::shared_ptr<Clickable>> clicked_vector;
	std::size_t iterator;
	clicked(std::vector<std::shared_ptr<Clickable>> clicked_vect, std::size_t it) : clicked_vector(clicked_vect), iterator(it) {}
};

/*
* Brief: Default state of the upgrade phase
* Param: GameManager reference
* Return: Nothing
* Note: This is the default screen of the upgrade phase. You can click on
*		on the different turret/consumable slots, go to player upgrade or start next wave
*/
void menu_select(GameManager& gm);

/*
* Brief: Constructs the confirmation menu
* Param: GameManager reference
* Return: A vector of clickables
* Note: This is used before finalizing every purchase and continuing to next wave
*/
std::vector<std::shared_ptr<Clickable>> construct_confirm_menu(GameManager& gm_);


/*
* Brief: Determines if the purchase should go through
* Param: GameManager reference
* Return: If yes or no was clicked
* Note: Uses construct_confirm_menu internally 
*/
bool confirm(GameManager& gm);

/*
* Brief: Tells if a menu has been clicked on
* Param: current mouse coordinates and a vector of clickables
* Return: Yes if a menu option has been clicked on, no otherwise
*/
bool clicked_on_menu(sf::Vector2f mousePos, std::vector<std::shared_ptr<Clickable>> clickables);

/*
* Brief: Tells if a menu has been clicked on
* Param: current mouse coordinates and a vector of vectors of clickables
* Return: Yes if a menu option has been clicked on, no otherwise
* Note: Iterates through the first vector and calls the above
*		clicked_on_menu on each sub-vector
*/
bool clicked_on_menu(sf::Vector2f mousePos, std::vector<std::shared_ptr<std::vector<std::shared_ptr<Clickable>>>> clickables);

/*
* Brief: Gets the clickable that has been clicked on
* Param: Mouse coordinates, a vector of vectors of clickables, an integer
* Return: a clicked that contains the vector that contains the clickable and the iterator that clickable is in
* Note: anyNum does nothing. The compiler could not distinguish between this getClickedMenu and the other one and reported errors
*/
clicked getClickedMenu(sf::Vector2f mousePos, std::vector<std::shared_ptr<std::vector<std::shared_ptr<Clickable>>>> clickables, int anyNum);

/*
* Brief: Gets the clickable that has been clicked on
* Param: Mouse coordinates, a vector of clickables
* Return: The position of the selected clickable in the vector
*/
std::size_t	getClickedMenu(sf::Vector2f mousePos, std::vector<std::shared_ptr<Clickable>> clickables);

/*
* Brief: Creates the turret/consumable upgrade squares
* Param: GameManager reference
* Return: A vector of clickables
* Note: These are the red/green squares that you can click on in the upgrade menu to
*		build/upgrade turrets and consumables
*/
std::vector<std::shared_ptr<Clickable>> create_upgrade_clickables(GameManager& gm);

/*
* Brief: Creates the start and exit buttons
* Param: GameManager reference
* Return: A vector of clickables
* Note: These are the start and exit buttons that allow you to either start or 
*		exit the game in the upper right and left hand corners
*/
std::vector<std::shared_ptr<Clickable>> create_start_stop(GameManager& gm);

/*
* Brief: Creates the turret/consumable squares and the start and stop buttons
* Param: GameManager reference
* Return: A vector of vectors of clickables
* Note: Simply calls create_start_stop and create_upgrade_clickables
*/
std::vector<std::shared_ptr<std::vector<std::shared_ptr<Clickable>>>> create_menus(GameManager& gm);

/*
* Brief: Draws a vector of clickables to the screen
* Param: Vector of clickables and the game display
* Return: Nothing
* Note: Doesn't display the clickables, only gets them ready to be displayed
*/
void draw_boxes(std::vector<std::shared_ptr<Clickable>> clickables, sf::RenderWindow& window);

/*
* Brief: Draws the game field
* Param: GameManager reference
* Return: Nothing
* Note: This includes the floors and the player
*/
void draw_game_field(GameManager& gm);

/*
* Brief: Draws everything
* Param: GameManager reference, a vector of vectors of clickables
* Return: Nothing
* Note: Simply calls draw_game_field and draw_boxes on each subvector of clickables
*/
void draw_all(GameManager& gm, std::vector<std::shared_ptr<std::vector<std::shared_ptr<Clickable>>>> clickables);

/*
* Brief: Draws the build menu for turrets and consumables
* Param: GameManager reference, type of menu to build, and a clicked representing the slot to build in
* Return: Nothing
* Note: Type can either be buildTurret, buildConsumable, upgradeTurret, upgradeConsumable to represent
*		each of the possible states that the upgrade clickable can represent
*/
void draw_build_menu(GameManager& gm, std::string type, clicked vector);

/*
* Brief: Draws the upgrade menu for a specific item
* Param: GameManager reference, type of item, clicked representing that item
* Return: Nothing
* Note: Creates the split menu comparing the current stats to the upgraded stats
*		the clicked represents a turret/consumable square
*		type holds if the clicked is representative of a turret or a consumable
*/
void draw_upgrade_menu(GameManager& gm, std::string type, clicked vector);

/*
* Brief: Draws the information box of the selected item
* Param: GameManager reference, name of item to display stats for, reference to vector of clickables
* Return: Nothing
* Note: Appends the vector with these extra clickables so that functionality of the original vector reamins
*/
void draw_info_box(GameManager& gm, std::string name, std::vector<std::shared_ptr<Clickable>>& menu);

/*
* Brief: Determines if the player can purchase the item 
* Param: GameManager reference, item name
* Return: True if the player has enough money to purchase, false otherwise
* Note: Runs the canPurchase below internally
*/
bool canPurchase(GameManager& gm, std::string item);

/*
* Brief: Determines if the player can afford something and purchases it if they can
* Param: GameManager, cost to buy
* Return: Nothing
* Note: If the player has enough, the money is deducted in this function for the purchase
*/
bool canPurchase(GameManager& gm, int cost);

/*
* Brief: Draws the player upgrade menu
* Param: GameManager reference
* Return: Nothing
* Note: Creates the menu that displays all the player upgrades accessed via
*		the button center bottom of the screen
*/
void draw_player_menu(GameManager& gm);

/*
* Brief: Draws the weapon equip/upgrade options
* Param: GameManager reference, name of weapon, vector of clickable reference
* Return: Nothing
* Note: Creates the equip/upgrade buttons for purchased weapons in the player upgrade menu
*/
void draw_weapon_equip(GameManager& gm, std::string name, std::vector<std::shared_ptr<Clickable>>& menu);

/*
* Brief: Draws the weapon equip menu
* Param: GameManager reference, Firearm reference
* Return: Nothing
* Note: Creates the menu that allows you to equip the firearm to either holstered or active slots
*/
void draw_equip_menu(GameManager& gm, Firearm& firearm);

/*
* Brief: Draws the repair menu for consumables
* Param: GameManager reference, clicked representing the consumable to be repaired
* Return: Nothing
* Note: Creates the menu that asks you if you want to repair the consumable
*/
void repair_consumable(GameManager& gm, clicked vector);