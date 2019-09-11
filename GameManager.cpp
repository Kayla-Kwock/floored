#include "stdafx.h"

//Constructor for the GameManager
GameManager::GameManager(std::vector<std::reference_wrapper<Floor>>& floors_) : floors(floors_){
	weapons.reserve(5);//Reserves 5 slots in weapon for the 5 purchasable guns in the game
	//This was done because when we appended the vector with a new weapon, the address of the 
	//	previous weapons would change, causing all the references to be wrong
	weapons.push_back(Firearm("Pistol"));//Create the player's starting weapon
	player.swap_equipped(weapons.at(0));//And equip it to both slots
	player.swap_holstered(weapons.at(0));
}

//Initializes game-specific variables
//This could be done in the constructor, however it is in its own function
//	so that it is very obvious where the UI settings are in case we need to change them
void GameManager::initialize() {
	window_ref.create(sf::VideoMode(1280, 768), "Game");
	window_ref.setFramerateLimit(120);
	font.loadFromFile("Fonts/Xenotron.ttf");
}

//Runs the game portion of the game
bool GameManager::phaseGame() {
	bool mbheld = false;//Mouse button held
	float dt = 0;//change in time
	bool end = false;//Game end (by killing all enemies)

	gameClock.restart();//Restart the game's clock
	//Below is the game loop. Manages player input and calculating
	//	new frames via the newPositions function
	while (window.isOpen() && !end)	{
		if (gameOver) {//If the game is over due to enemy attacks
			return true;
		}
		frameTime = frameClock.restart();//Gets the time from last frame
		dt = frameTime.asSeconds();//in seconds (accurate to the microsecond)

		while (window.pollEvent(event)){//If there is any player input
			if (event.type == sf::Event::Closed)//If the window was closed
				window.close();

			if (event.type == event.MouseButtonPressed) {//If a mouse button was pressed/held
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
					mbheld = true;
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
					player.switch_weapons();
				}
			}
			if (event.type == event.MouseButtonReleased) {//If a mouse button was released
				mbheld = false;
			}
			if (event.type == event.KeyPressed) {//If a key on the keyboard was pressed
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
					player.moveUpFloor();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
					player.moveDownFloor();
				}
			}
		}
		if (mbheld) {//If the player has clicked or is holding the LMB in this frame
			player.shoot_equipped();//Shoot the equipped gun
		}
		//Below handles when enemies are spawned
		//	Spawns a new enemy every half second
		gameTime = gameClock.getElapsedTime();
		if (gameTime.asMilliseconds() >= 500) {
			spawn(window_ref, floors);
			gameClock.restart();
		}
		//Below handles frame refreshing
		window.clear();
		//Calculates new enemy positions and if the all enemies has been killed
		end = newPositions(*this, dt);
		window.draw(player.getSprite());
		window.display();
	}
	return false;//False if the wave has been successfully completed
}

//Loads the game for the next wave
void GameManager::phaseLoading(int wave_) {
	//Put up a loading screen (object construction takes a while)
	window.clear();
	sf::Texture loadingscreenimage;
	sf::Sprite loadingscreen;
	loadingscreenimage.loadFromFile("Screens/LoadingScreen.png");
	loadingscreen.setTexture(loadingscreenimage);
	window.draw(loadingscreen);
	window.display();

	//Reset the shaft hp, create new enemies, and reload Firearms with updated Projectiles
	shaft.resetHP();
	create_set(floors, wave_);
	for (std::size_t i = 0; i < floors.size(); i++) {
		for (std::size_t j = 0; j < floors[i].get().getTurrets().size(); j++) {
			floors[i].get().getTurrets().at(j).getFirearm().reload();
		}
		//If the consumable is only damaged, repair it for free!
		for (std::size_t k = 0; k < floors[i].get().getConsumables().size(); k++) {
			if (floors[i].get().getConsumables().at(k).isActive()) {
				floors[i].get().getConsumables().at(k).reload();
			}
		}
	}
	player.getEquipped().reload();
	player.getHolstered().reload();
	window.clear();//Clear the loading screen
}

//Handles the upgrade screen inbetween waves
void GameManager::phaseUpgrade(){
	all_sfx[19].stop();//Stop the Cat Gun's sound effect!!!
	NyanOffset = 0;//Reset the Cat Gun's SFX position to the beginning
	nextWave = false;//Reset the bool that triggers the next wave of enemies
	while (!nextWave){
		window.clear();
		menu_select(*this);//Draw the menus (prepare yourself)
	}
}

//Adds the purchased gun to the weapons vector
void GameManager::purchaseGun(std::string gun) {
	weapons.emplace_back(Firearm(gun));
}

//Checks if the player has already purchased a specific gun
bool GameManager::hasPurchasedGun(std::string gun) {
	for (std::size_t i = 0; i < weapons.size(); i++) {
		if (gun == weapons[i].getName()) {
			return true;
		}
	}
	return false;
}

//Getter for floors vector
std::vector<std::reference_wrapper<Floor>>& GameManager::getFloors() {
	return this->floors;
}

//Getter for text font
sf::Font& GameManager::getFont() {
	return font;
}

//Getter for display
sf::RenderWindow& GameManager::getWindow() {
	return window;
}

//Getter for Elevator Shaft
Shaft& GameManager::getShaft(){
	return shaft;
}

//Getter for Player
Player& GameManager::getPlayer() {
	return player;
}

//Setter for gameOver
void GameManager::setGameOver(bool state){
	gameOver = state;
}

//Getter and setter for nextWave
//	startNextWave is worded as a question
//	as in "start the next wave?"
bool GameManager::startNextWave() {
	return nextWave;
}

void GameManager::setNextWave() {
	nextWave = true;
}

//Gets a reference to a specific gun
Firearm& GameManager::getGun(std::string name) {
	for (std::size_t i = 0; i < weapons.size(); i++) {
		if (weapons[i].getName() == name) {
			return weapons[i];
		}
	}
}

//Getter and setter for the game's current wave
int GameManager::getWave() {
	return currentWave;
}

void GameManager::setWave(int wave_) {
	currentWave = wave_;
}