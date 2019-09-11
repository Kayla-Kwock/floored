#pragma once

#include "stdafx.h"

/* A Clickable is anything you can interact with by clicking on it.
 * text are the words you see inside the box
 * shape is the overall shape of the box
 * function is the purpose of the box, like to buy/sell a turret
 * turret and consumable are used for the turret/consumable upgrade squares
 *	they hold a reference to the actual object the box is supposed to represent
 * name is an optional tag given to turret/consumable upgrade squares
 *	the purpose is to be able to tell if the box represents a turret or a consumable
 *	and wether or not it is a purchase or an upgrade
 */
class Clickable: public sf::Drawable {
	private:
		sf::Text text;
		sf::RectangleShape shape;
		std::string function;
		std::reference_wrapper<Turret> turret;
		std::reference_wrapper<Consumable> consumable;
		std::string name;
	public:
	/*
	* Brief: Constructor for transparent clickables
	* Param: Measurements and location of the box and the box function
	* Return: Nothing.
	* Note: Used when clickable text is variable (sell price) or for expendable clickables
	* This is layerd on top of a clickable that has variable text.
	*/
	Clickable(int x_, int y_, int length_, int height_,std::string function_); 
		
	/*
	* Brief: Constructor for opaque clickables
	* Param: Measurements and location of the box and the box function
	* Return: Nothing.
	* Note: Used for every clickable with text inside of it
	*/
	Clickable(
		int x_,
		int y_,
		int length_,
		int height_,
		std::string text_,
		sf::Font& font_,
		int text_size_); 

	/*
	* Brief: Constructor for upgrade outlines
	* Param: Measurements and location of the box and the box function
	* Return: Nothing.
	* Note: Used to create the red and green turret/consumable squares
	*/
	Clickable(GameManager& gm, int floor, int slot, std::string ConsOrTurret, sf::Color color, int outlineThickness);
	
	/*
	* Brief: Draws the clickable to the RenderTarget
	* Param: The RenderTarget (a RenderWindow) and RenderState
	* Return: Nothing
	*/
	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const override;

	/*
	* Brief: Triggers the function of the clickable
	* Param: A GameManager
	* Return: Nothing
	* Note: Exclusively used on the main upgrade screen
	*/
	void activate(GameManager& gm);

	/*
	* Brief: Triggers the function of a clickable
	* Param: GameManager, an integer representing its position, and the name
	* Return: Nothing
	* Note: Used for the turret/consumable square clickables
	*/
	void activate(GameManager& gm, int selected_menu, std::string name_);

	/*
	* Brief: Gets the text of the clickable
	* Param: Nothing
	* Return: An sf::Text of the clickable's text
	*/
	sf::Text& getText();

	/*
	* Brief: Gets the box of the clickable
	* Param: Nothing
	* Return: The box created by the clickable
	*/
	sf::RectangleShape& getShape();

	/*
	* Brief: Returns the function of a clickable
	* Param: Nothing
	* Return: A string representing the clickable's usage
	*/
	std::string getFunction();

	/*
	* Brief: Returns the name of a clickable
	* Param: Nothing
	* Return: A string representing the name of the clickable
	* Note: Used exclusively on consumables to determine
	* what stats to show in the upgrade menu
	*/
	std::string getName();

	/*
	* Brief: Returns a reference to the turret a turret clickable represents
	* Param: Nothing
	* Return: A reference to a turret
	*/
	Turret& getTurret();

	/*
	* Brief: Returns a reference to the consumable a consumable clickable represents
	* Param: Nothing 
	* Return: A reference to a consumable
	*/
	Consumable& getConsumable();
};