#pragma once

#include "stdafx.h"

/* GameManager controls the game and is created upon program start
 * window is the display of the game
 * window_ref is a reference to window 
 * floors is all the floors in the game
 * frameClock and frameTime keep track of the interval between frames
 * gameClock and gameTime keep track of the overall game timing
 *		used to determine when to spawn the next enemies
 * event takes in the player's inputs
 * font is the font of the text used
 * shaft is the elevator shaft
 * nextWave tells wether or not to spawn the next wave of enemies
 * currentWave saves the current wave number of the game
 * gameOver tells if the player has lost the game
 * weapons are all the weapons purchased by the player
 * player is the player
 * player_ref is a reference to the player
 */
class GameManager {
private:
	sf::RenderWindow window;
	sf::RenderWindow& window_ref = window;
	std::vector<std::reference_wrapper<Floor>>& floors;
	sf::Clock frameClock, gameClock;
	sf::Time frameTime, gameTime;
	sf::Event event;
	sf::Font font;
	Shaft shaft;
	bool nextWave;
	int currentWave;
	bool gameOver = false;
	std::vector<Firearm> weapons;
	Player player;
	Player& player_ref = player;
public:

	/*
	* Brief: Constructor
	* Param: A reference to a vector of floors
	* Return: Nothing
	*/
	GameManager(std::vector<std::reference_wrapper<Floor>>& floors_);

	/*
	* Brief: Runs all intialization requirements (loading sounds, creating initial clickables etc.)
	* Param: Nothing
	* Return: Nothing
	*/
	void initialize();

	/*
	* Brief: Runs the action part of the game
	* Param: Nothing
	* Return: Nothing
	*/
	bool phaseGame();

	/*
	* Brief: Runs the loading inbetween the upgrade screen and action
	* Param: The current wave
	* Return: Nothing
	*/
	void phaseLoading(int wave_);

	/*
	* Brief: Runs the upgrade part of the game
	* Param: Nothing
	* Return: Nothing
	*/
	void phaseUpgrade();

	/*
	* Brief: Used to append a new Firearm onto weapons
	* Param: The name of desired Firearm
	* Return: Nothing
	*/
	void purchaseGun(std::string gun);

	/*
	* Brief: Checks if the desired Firearm is already in weapons
	* Param: The name of desired Firearm
	* Return: Yes if Firearm has already been purchased, no otherwise
	*/
	bool hasPurchasedGun(std::string gun);

	/*
	* Brief: Getter for all the floors
	* Param: Nothing
	* Return: A reference to the vector of floors
	*/
	std::vector<std::reference_wrapper<Floor>>& getFloors();

	/*
	* Brief: Getter for the font used by the game
	* Param: Nothing
	* Return: Reference to the font
	*/
	sf::Font& getFont();

	/*
	* Brief: Getter for the display window
	* Param: Nothing
	* Return: Reference to the display window
	*/
	sf::RenderWindow& getWindow();

	/*
	* Brief: Getter for the elevator shaft
	* Param: Nothing
	* Return: Reference to the elevator shaft
	*/
	Shaft& getShaft();

	/*
	* Brief: Getter for the player
	* Param: Nothing
	* Return: Reference to the player
	*/
	Player& getPlayer();

	/*
	* Brief: Setter for gameover
	* Param: gameover state
	* Return: Nothing
	*/
	void setGameOver(bool state);

	/*
	* Brief: Getter and setter for nextWave
	* Param: Nothing and nothing
	* Return: state of nextWave and nothing
	*/
	bool startNextWave();
	void setNextWave();

	/*
	* Brief: Used to find a specific Firearm inside of weapons
	* Param: The name of desired Firearm
	* Return: Reference to desired Firearm
	*/
	Firearm& getGun(std::string name);

	/*
	* Brief: Getters and setters for the current wave number
	* Param: Nothing and wave number
	* Return: Current wave number and nothing
	*/
	int getWave();
	void setWave(int wave_);
};