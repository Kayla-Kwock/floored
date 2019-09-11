#include "stdafx.h"

/*Preamble
 * CAUTION - THIS IS THE 700 LINE FILE (800 including comments)
 * PLEASE READ THIS LAST, AS THERE IS MUCH FROM EVERYOTHER FILE
 * Also, get some snacks or something. This is gonna take a while
 * 
 * The only thing you really need to focus on is the string inside each Clickable constructor call
 *	All the other numbers and function calls handle box location, font and font size
 *	The string determines what the purpose of the Clickable is and what is written inside of it
 *
 * Each function generally follows one of two layouts
 *	Generate Clickables and pass them onto a provided vector of Clickables
 *	Generate Clickables and wait for you to click on them
 *	
 * For the first layout, it generally creates a vector called Construct
 *	Construct holds all the created Clickables to be returned
 * For the second layout, it may also create a Construct vector
 *	With the exception of confirm() and draw_equip_menu() which use confirm_menu instead of Construct
 *	This is followed by a player input checker, which waits and checks for player clicks
 *		The player input checker finds if the mouse position is inside a bounding square of a Clickable	
 *		Next it determines what the text inside that Clickable says
 *		Finally, it cross-checks with a list of IF cases to determine which actions to take
 *
 * The function of the Clickable is plainly stated in the Clickable's constructor
 *	Simply match the function's text to one of the IF cases to determine what the clickable will do.
 *	For example, in confirm(), it calls construct_confirm_menu() which returns a vector of Clickables
 *		Then there is a player input checker that has the options "Yes" and "No"
 *		If "Yes" was the function of the Clickable selected, it will return true
 *		If "No" was the function of the Clickable selected, it will return false
 *	Every player input checker follows this process
 *
 * StringStream is used for Clickables that changes text depending on certain variables (Ex. Player money)
 *	StringStream recognizes '\n' as a new line and will thus effectively put anything after it on a new line
 *	It needs to be cleared after every input as to not have previous Clickable functions spill over
 *	To do this, we call name.str(std::string()) where name is the name of the StringStream
 */
void menu_select(GameManager& gm) {
	sf::Vector2f mousePos;
	sf::Event event;

	//Begin Player Input Checking---------------------------
	while (gm.getWindow().isOpen() && !gm.startNextWave()) {
		//The menus need to be refreshed every frame as the Clickable needs to change to an upgrade clickable if
		//	you have purchased a Turret/Consumable in that slot. Likewise, it needs to switch to a build clickable if you
		//	sold a Turret/Consumable
		std::vector<std::shared_ptr<std::vector<std::shared_ptr<Clickable>>>> all_menus = create_menus(gm);
		gm.getWindow().clear();
		draw_all(gm, all_menus);
		while (gm.getWindow().pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				gm.getWindow().close();
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				mousePos = gm.getWindow().mapPixelToCoords(sf::Mouse::getPosition(gm.getWindow()));//Save the mouse position
				if (clicked_on_menu(mousePos, all_menus)) {
					clicked selected_menu = getClickedMenu(mousePos, all_menus, 1);//Get the Clickable that was clicked on
					//Selects the appropriate menu to create depending on what was clicked
					if (selected_menu.clicked_vector.at(selected_menu.iterator)->getFunction() == "buildTurret") {
						draw_build_menu(gm, "buildTurret", selected_menu);
					}
					else if (selected_menu.clicked_vector.at(selected_menu.iterator)->getFunction() == "buildConsumable") {
						draw_build_menu(gm, "buildConsumable", selected_menu);
					}
					else if (selected_menu.clicked_vector.at(selected_menu.iterator)->getFunction() == "upgradeTurret") {
						draw_upgrade_menu(gm, "upgradeTurret", selected_menu);
					}
					else if (selected_menu.clicked_vector.at(selected_menu.iterator)->getFunction() == "upgradeConsumable") {
						draw_upgrade_menu(gm, "upgradeConsumable", selected_menu);
					}
					else if (selected_menu.clicked_vector.at(selected_menu.iterator)->getFunction() == "Player\nUpgrades") {
						draw_player_menu(gm);
					}
					else if (confirm(gm)) {
						selected_menu.clicked_vector.at(selected_menu.iterator)->activate(gm);
					}
				}
			}
		}
	}
}

//Constructs the Confimation menu
std::vector<std::shared_ptr<Clickable>> construct_confirm_menu(GameManager& gm_) {
	std::vector<std::shared_ptr<Clickable>> construct;
	construct.push_back(std::make_shared<Clickable>(Clickable(gm_.getWindow().getSize().x / 2 - 200, gm_.getWindow().getSize().y / 2 - 150, 400, 300, "Are you sure?", gm_.getFont(), 30)));
	construct.push_back(std::make_shared<Clickable>(Clickable(gm_.getWindow().getSize().x / 2 - 150, gm_.getWindow().getSize().y / 2 + 50, 100, 50, "Yes", gm_.getFont(), 30)));
	construct.push_back(std::make_shared<Clickable>(Clickable(gm_.getWindow().getSize().x / 2 + 50, gm_.getWindow().getSize().y / 2 + 50, 100, 50, "No", gm_.getFont(), 30)));
	return construct;
}

bool confirm(GameManager& gm) {
	sf::Event event;
	sf::Vector2f mousePos = gm.getWindow().mapPixelToCoords(sf::Mouse::getPosition(gm.getWindow()));
	std::size_t confirmation_choice;
	std::vector<std::shared_ptr<Clickable>> confirm_menu = construct_confirm_menu(gm);

	draw_boxes(confirm_menu, gm.getWindow());
	gm.getWindow().display();
	//Begin Player Input Checking---------------------------
	while (true) {
		while (gm.getWindow().isOpen()) {//While window is open
			while (gm.getWindow().pollEvent(event)) {//While there is player input
				if (event.type == sf::Event::Closed) {//If the display is closed
					gm.getWindow().close();//Close the game
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					sf::Vector2f mousePos = gm.getWindow().mapPixelToCoords(sf::Mouse::getPosition(gm.getWindow()));
					if (clicked_on_menu(mousePos, confirm_menu)) {//If a Clickable was clicked on
						confirmation_choice = getClickedMenu(mousePos, confirm_menu);
						//Execute the appropriate option
						if (confirm_menu[confirmation_choice]->getFunction() == "Yes") {
							return true;
						}
						else if (confirm_menu[confirmation_choice]->getFunction() == "No") {
							return false;
						}
					}
				}
			}
		}
	}
}

//Checks if a Clickable in a given vector has been clicked on
bool clicked_on_menu(sf::Vector2f mousePos, std::vector<std::shared_ptr<Clickable>> clickables) {
	for (std::size_t i = 0; i < clickables.size(); i++) {
		if (clickables[i]->getShape().getGlobalBounds().contains(mousePos)) {//If the cursor is within the bounds of the box
			return true;
		}
	}
	return false;
}

//This function simply calls the one above it, but can be given a vector of vectors of clickables as a parameter
//	Allowing for multiple vectors to be compared using one function call
bool clicked_on_menu(sf::Vector2f mousePos, std::vector<std::shared_ptr<std::vector<std::shared_ptr<Clickable>>>> clickables) {
	for (std::size_t i = 0; i < clickables.size(); i++) {
		if (clicked_on_menu(mousePos, *clickables[i])) {//If something has been clicked on
			return true;
		}
	}
	return false;
}

//Obtain the paramaters to retrieve the Clickable that was clicked on
//	Similar to the one below, but used for a vector of vectors (like the upgrade menu)
clicked getClickedMenu(sf::Vector2f mousePos, std::vector<std::shared_ptr<std::vector<std::shared_ptr<Clickable>>>> clickables, int anyNum) {
	for (std::size_t i = 0; i < clickables.size(); i++) {
		for (int j = clickables[i]->size() - 1; j >= 0; j--) {
			if (clickables[i]->at(j)->getShape().getGlobalBounds().contains(mousePos)) {//If the cursor is within the bounds of the box
				return clicked(*clickables[i], j);
			}
		}
	}
}
//Obtain the parameters to retrieve the Clickable that was clicked on
//	Similar to the one above, but used for single vectors (like the confirm menu)
std::size_t	getClickedMenu(sf::Vector2f mousePos, std::vector<std::shared_ptr<Clickable>> clickables) {
	for (std::size_t i = clickables.size() - 1; i >= 0; i--) {
		if (clickables[i]->getShape().getGlobalBounds().contains(mousePos)) {//If the cursor is within the bounds of the box
			return i;
		}
	}
}

//Creates the turret/consumable upgrade squares and the player upgrade Clickable
std::vector<std::shared_ptr<Clickable>> create_upgrade_clickables(GameManager& gm) {
	std::vector<std::shared_ptr<Clickable>> construct;
	for (std::size_t i = 0; i < gm.getFloors().size(); i++) {//Per floor
		for (std::size_t j = 1; j <= 3; j++) {
			construct.push_back(std::make_shared<Clickable>(Clickable(gm, i, j, "Turret", sf::Color::Red, 2)));
		}
		for (std::size_t k = 1; k <= 2; k++) {
			construct.push_back(std::make_shared<Clickable>(Clickable(gm, i, k, "Cons", sf::Color::Green, 2)));
		}
	}
	construct.push_back(
		std::make_shared<Clickable>(Clickable(gm.getWindow().getSize().x/2 - 125, 650, 250, 75,"Player\nUpgrades", gm.getFont(), 30)));
	return construct;
}

//Create the start/exit buttons that start the next wave or quit the game
//	Also creates the wave counter that displays what wave you are on
std::vector<std::shared_ptr<Clickable>> create_start_stop(GameManager& gm) {
	std::vector<std::shared_ptr<Clickable>> construct;
	std::stringstream stream;
	construct.push_back(std::make_shared<Clickable>(Clickable(0, 0, 175, 50, "start", gm.getFont(), 30)));
	construct.push_back(std::make_shared<Clickable>(Clickable(gm.getWindow().getSize().x- 100, 0, 100, 50, "exit", gm.getFont(), 30)));
	stream << "\nWave	" << gm.getWave() << "/15" << std::endl;
	construct.push_back(std::make_shared<Clickable>(Clickable(490, 0, 300, 50, stream.str(), gm.getFont(), 30)));
	return construct;
}

//Creates all the clickables that are on the home screen
//	Calls other functions and returns a vector of the results
std::vector<std::shared_ptr<std::vector<std::shared_ptr<Clickable>>>> create_menus(GameManager& gm){
	std::vector<std::shared_ptr<std::vector<std::shared_ptr<Clickable>>>> construct;
	construct.push_back(std::make_shared<std::vector<std::shared_ptr<Clickable>>>(create_upgrade_clickables(gm)));
	construct.push_back(std::make_shared<std::vector<std::shared_ptr<Clickable>>>(create_start_stop(gm)));
	return construct;
}

//Draws the box and the text of a Clickable given a vector
void draw_boxes(std::vector<std::shared_ptr<Clickable>> clickables, sf::RenderWindow& window) {
	for (int i = 0; i < clickables.size(); i++) {
		window.draw(clickables[i]->getShape());
		window.draw(clickables[i]->getText());
	}
}

//Draws the player, floor, turrets, and consumables to the display
void draw_game_field(GameManager& gm) {
	gm.getWindow().draw(gm.getShaft().getSprite());
	gm.getWindow().draw(gm.getPlayer().getSprite());
	for (std::size_t i = 0; i < gm.getFloors().size(); i++) {//per floor
		gm.getWindow().draw(gm.getFloors().at(i).get().getSprite());
		for (std::size_t j = 0; j < gm.getFloors().at(i).get().getConsumables().size(); j++) {//per consumable
			gm.getWindow().draw(gm.getFloors().at(i).get().getConsumables().at(j).getSprite());
		}
		for (std::size_t k = 0; k < gm.getFloors().at(i).get().getTurrets().size(); k++) {//per turret
			gm.getWindow().draw(gm.getFloors().at(i).get().getTurrets().at(k).getSprite());
		}
	}
}

//Draws all the Clickables created and the game field
void draw_all(GameManager& gm, std::vector<std::shared_ptr<std::vector<std::shared_ptr<Clickable>>>> clickables) {
	draw_game_field(gm);
	for (std::size_t i = 0; i < clickables.size(); i++) {
		draw_boxes(*clickables[i], gm.getWindow());
	}
	gm.getWindow().display();	
}

//Draws the build menu for Turrets and Consumables
void draw_build_menu(GameManager& gm, std::string type, clicked vector) {
	std::vector<std::shared_ptr<Clickable>> construct;
	sf::Vector2f mousePos;
	std::string can_purchase;
	std::stringstream stream;
	bool goBack = false;

	//Begin constructing build menu
	construct.push_back(std::make_shared<Clickable>(Clickable(50, 50, 1180, 668, "", gm.getFont(), 0)));//menu background
	construct.push_back(std::make_shared<Clickable>(Clickable(50, 450, 1180, 268, "", gm.getFont(), 0)));//lower third bounding box
	construct.push_back(std::make_shared<Clickable>(Clickable(50, 450, 800, 268, "", gm.getFont(), 0)));//description bounding box
	if (type == "buildTurret") {//Displays Turret options
		construct.push_back(std::make_shared<Clickable>(Clickable(100, 75, 1080, 50, "Peashooter", gm.getFont(), 40)));
		construct.push_back(std::make_shared<Clickable>(Clickable(100, 150, 1080, 50, "Heavy Machine Gun", gm.getFont(), 40)));
		construct.push_back(std::make_shared<Clickable>(Clickable(100, 225, 1080, 50, "Tachanka", gm.getFont(), 40)));
		construct.push_back(std::make_shared<Clickable>(Clickable(100, 300, 1080, 50, "Railgun", gm.getFont(), 40)));
		construct.push_back(std::make_shared<Clickable>(Clickable(100, 375, 1080, 50, "Lazer Turret", gm.getFont(), 40)));
	}
	else if (type == "buildConsumable") {//Displays Consumable options
		construct.push_back(std::make_shared<Clickable>(Clickable(100, 75, 1080, 50, "Mine", gm.getFont(), 40)));
		construct.push_back(std::make_shared<Clickable>(Clickable(100, 150, 1080, 50, "Wall", gm.getFont(), 40)));
		construct.push_back(std::make_shared<Clickable>(Clickable(100, 225, 1080, 50, "Bandit Wire", gm.getFont(), 40)));
		construct.push_back(std::make_shared<Clickable>(Clickable(100, 300, 1080, 50, "Buzzsaw", gm.getFont(), 40)));
		construct.push_back(std::make_shared<Clickable>(Clickable(100, 375, 1080, 50, "Gulper", gm.getFont(), 40)));
	}
	construct.push_back(std::make_shared<Clickable>(Clickable(1050, 593, 125, 70, "Go\nBack", gm.getFont(), 25)));//Back option
	stream << "Money\n" << gm.getPlayer().getMoney();
	construct.push_back(std::make_shared<Clickable>(Clickable(900, 593, 125, 70, stream.str(), gm.getFont(), 25)));//Player money
	//These burners are here because in draw_info_box, we delete the previous infomation boxes and draw new ones
	//	These are for the first time we click on an item, when there is no previous information box
	construct.push_back(std::make_shared<Clickable>(Clickable(0, 0, 0, 0, "", gm.getFont(), 0)));//Burner
	construct.push_back(std::make_shared<Clickable>(Clickable(0, 0, 0, 0, "", gm.getFont(), 0)));//Burner

	//Begin Player Input Checking---------------------------
	sf::Event event;
	while (gm.getWindow().isOpen() && !goBack) {
		draw_boxes(construct, gm.getWindow());
		gm.getWindow().display();
		while (gm.getWindow().pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				gm.getWindow().close();
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				mousePos = gm.getWindow().mapPixelToCoords(sf::Mouse::getPosition(gm.getWindow()));
				if (clicked_on_menu(mousePos, construct)) {
					std::size_t selected_menu = getClickedMenu(mousePos, construct);
					if (construct[selected_menu]->getFunction() == "Go\nBack") {
						goBack = true;
					}
					else if (construct[selected_menu]->getFunction() == "Purchase") {
						if (confirm(gm)) {
							if (canPurchase(gm, can_purchase)) {//If you have enough money to purchase the item
								vector.clicked_vector.at(vector.iterator)->activate(gm, vector.iterator, can_purchase);
								goBack = true;
							}
						}
					}
					else {//Display the information of the Turret/Consumable selected
						can_purchase = construct[selected_menu]->getFunction();
						draw_info_box(gm, can_purchase, construct);
					}
				}
			}
		}
	}
}

//Draws the upgrade menu
//	This one might look bad, but it's fairly simple since there are 2 sets of item stats
//	an upgraded set and the current set.
void draw_upgrade_menu(GameManager& gm, std::string type, clicked vector) {
	std::vector<std::shared_ptr<Clickable>> construct;
	sf::Vector2f mousePos;
	//stream is the list of current stats
	//	ustream is the list of the upgraded stats
	std::stringstream stream, ustream;
	bool goBack = false;
	stats info, upgradedInfo;

	construct.push_back(std::make_shared<Clickable>(Clickable(240, 84, 800, 625, "", gm.getFont(), 0)));//main box
	construct.push_back(std::make_shared<Clickable>(Clickable(240, 159, 400, 75, "Current Stats", gm.getFont(), 30)));//Current stats header
	construct.push_back(std::make_shared<Clickable>(Clickable(640, 159, 400, 75, "Upgraded Stats", gm.getFont(), 30)));//Upgraded stats header
	if (type == "upgradeTurret") {//If it's a Turret
		construct.push_back(std::make_shared<Clickable>(
			Clickable(240, 84, 800, 75, vector.clicked_vector.at(vector.iterator)->getTurret().getName(), gm.getFont(), 40)));//name of item upgrading
		//For selling, since the sell amount is variable there is a transparent Clickable (holds the Selling function)
		//	and an opaque Clickable (holds the selling details like how much you get back)
		stream << "Sell: \n" << getUpgrade(
			vector.clicked_vector.at(vector.iterator)->getTurret().getName(), 
			vector.clicked_vector.at(vector.iterator)->getTurret().getLevel()).cost * 0.8;//Gets the selling price of the Object
		construct.push_back(std::make_shared<Clickable>(Clickable(458, 584, 168, 100, stream.str(), gm.getFont(), 25)));//sell amount
		construct.push_back(std::make_shared<Clickable>(Clickable(458, 584, 168, 100, "Sell")));//sell Clickable
		stream.str(std::string());
		info = getUpgrade(
			vector.clicked_vector.at(vector.iterator)->getTurret().getName(), vector.clicked_vector.at(vector.iterator)->getTurret().getLevel());//Get current stats
		upgradedInfo = getUpgrade(
			vector.clicked_vector.at(vector.iterator)->getTurret().getName(), vector.clicked_vector.at(vector.iterator)->getTurret().getLevel() + 1);//Get upgraded stats
		stream << "Level: " << vector.clicked_vector.at(vector.iterator)->getTurret().getLevel() << "\nDamage: " << info.damage << "\nPunch: " << info.punch;//Print those stats out
		ustream << "Level: " << vector.clicked_vector.at(vector.iterator)->getTurret().getLevel() + 1 << "\nDamage: " << upgradedInfo.damage << "\nPunch: " << upgradedInfo.punch;
		construct.push_back(std::make_shared<Clickable>(Clickable(651, 584, 168, 100, "Purchase", gm.getFont(), 20)));//Purchase
	}
	else if (type == "upgradeConsumable") { //If it is a Consumable
		construct.push_back(std::make_shared<Clickable>(Clickable(
			240, 84, 800, 75, vector.clicked_vector.at(vector.iterator)->getConsumable().getName(), gm.getFont(), 40)));//name of item upgrading
		//For selling, since the sell amount is variable there is a transparent Clickable (holds the Selling function)
		//	and an opaque Clickable (holds the selling details like how much you get back)
		stream << "Sell: \n" << getUpgrade(vector.clicked_vector.at(vector.iterator)->getConsumable().getName(),
			vector.clicked_vector.at(vector.iterator)->getConsumable().getLevel()).cost * 0.8;//Calculate sell amount
		construct.push_back(std::make_shared<Clickable>(Clickable(458, 584, 168, 100, stream.str(), gm.getFont(), 20)));//sell amount
		construct.push_back(std::make_shared<Clickable>(Clickable(458, 584, 168, 100, "Sell")));//sell Clickable
		stream.str(std::string());
		info = getUpgrade(vector.clicked_vector.at(vector.iterator)->getConsumable().getName(), 
			vector.clicked_vector.at(vector.iterator)->getConsumable().getLevel());//Get current stats
		upgradedInfo = getUpgrade(vector.clicked_vector.at(vector.iterator)->getConsumable().getName(),
			vector.clicked_vector.at(vector.iterator)->getConsumable().getLevel() + 1);//Get upgraded stats
		stream << "Level: " << vector.clicked_vector.at(vector.iterator)->getConsumable().getLevel();
		ustream << "Level: " << vector.clicked_vector.at(vector.iterator)->getConsumable().getLevel()+1;
		construct.push_back(std::make_shared<Clickable>(Clickable(651, 584, 168, 50, "Purchase", gm.getFont(), 15)));//Purchase
		construct.push_back(std::make_shared<Clickable>(Clickable(651, 634, 168, 50, "Repair", gm.getFont(), 15)));//Repair
		
		//Determine what stats need to be displayed by what kind of consumable it is
		if (vector.clicked_vector.at(vector.iterator)->getName() == "Mine") {
			stream << "\nDamage: " << info.damage;
			ustream << "\nDamage: " << upgradedInfo.damage;
		}
		else if (vector.clicked_vector.at(vector.iterator)->getName() == "Wall") {
			stream << "\nHealth: " << info.hp;
			ustream << "\nHealth: " << upgradedInfo.hp;
		}
		else if (vector.clicked_vector.at(vector.iterator)->getName() == "Bandit Wire") {
			stream << "\nDamage: " << info.damage;
			ustream << "\nDamage: " << upgradedInfo.damage;
		}
		else if (vector.clicked_vector.at(vector.iterator)->getName() == "Buzzsaw") {
			stream << "\nDamage: " << info.damage;
			ustream << "\nDamage: " << upgradedInfo.damage;
			stream << "\nHealth: " << info.hp;
			ustream << "\nHealth: " << upgradedInfo.hp;
		}
		else if (vector.clicked_vector.at(vector.iterator)->getName() == "Gulper") {
			stream << "\nDamage: " << info.damage;
			ustream << "\nDamage: " << upgradedInfo.damage;
		}
	}
	else {//If it is a player Firearm
		construct.push_back(std::make_shared<Clickable>(Clickable(240, 84, 800, 75, type, gm.getFont(), 40)));//name of item upgrading
		info = getUpgrade(type, gm.getGun(type).getLevel());
		upgradedInfo = getUpgrade(type, gm.getGun(type).getLevel() + 1);
		stream << "Level: " << gm.getGun(type).getLevel();
		ustream << "Level: " << gm.getGun(type).getLevel() + 1;
		stream << "\nDamage: " << info.damage << "\nPunch: " << info.punch;
		ustream << "\nDamage: " << upgradedInfo.damage << "\nPunch: " << upgradedInfo.punch;
		construct.push_back(std::make_shared<Clickable>(Clickable(651, 584, 168, 100, "Purchase", gm.getFont(), 20)));//Purchase
	}
	construct.push_back(std::make_shared<Clickable>(Clickable(240, 234, 400, 325, stream.str(), gm.getFont(), 30)));//Current stats
	construct.push_back(std::make_shared<Clickable>(Clickable(640, 234, 400, 325, ustream.str(), gm.getFont(), 30)));//Upgraded stats
	stream.str(std::string());
	stream << "\n\nCost:\n$" << upgradedInfo.cost<< "\nMoney:\n$" << gm.getPlayer().getMoney();
	construct.push_back(std::make_shared<Clickable>(Clickable(265, 584, 168, 100, stream.str(), gm.getFont(), 20)));//Cost
	construct.push_back(std::make_shared<Clickable>(Clickable(844, 584, 168, 100, "Go Back", gm.getFont(), 20)));//Go back
	
	//Begin Player Input Checking---------------------------
	sf::Event event;
	while (gm.getWindow().isOpen() && !goBack) {
		draw_boxes(construct, gm.getWindow());
		gm.getWindow().display();
		while (gm.getWindow().pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				gm.getWindow().close();
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				mousePos = gm.getWindow().mapPixelToCoords(sf::Mouse::getPosition(gm.getWindow()));
				if (clicked_on_menu(mousePos, construct)) {
					std::size_t selected_menu = getClickedMenu(mousePos, construct);
					//Determine the appropriate path to follow
					if (construct[selected_menu]->getFunction() == "Go Back") {
						goBack = true;
					}
					else if (construct[selected_menu]->getFunction() == "Purchase") {
						if (confirm(gm)) {
							if (canPurchase(gm, upgradedInfo.cost)) {
								if (type == "upgradeTurret") {
									vector.clicked_vector.at(vector.iterator)->getTurret().upgrade();
									goBack = true;
								}
								else if (type == "upgradeConsumable") {//Upgrading consumables also repair them
									vector.clicked_vector.at(vector.iterator)->getConsumable().upgrade();
									vector.clicked_vector.at(vector.iterator)->getConsumable().reload();
									goBack = true;
								}
								else {//Else the item is a player gun
									gm.getGun(type).upgrade();
									goBack = true;
								}
							}
						}
					}
					else if (construct[selected_menu]->getFunction() == "Repair") {
						repair_consumable(gm, vector);
						goBack = true;
					}
					else if (construct[selected_menu]->getFunction() == "Sell") {
						if (confirm(gm)) {
							if (type == "upgradeTurret") {//If we want to sell a Turret
								gm.getPlayer().setMoney(
									getUpgrade(vector.clicked_vector.at(vector.iterator)->getTurret().getName(),
										vector.clicked_vector.at(vector.iterator)->getTurret().getLevel()).cost * 0.8);//Refund the money
								for (std::size_t i = 0; i < gm.getFloors().at(floor(vector.iterator / 5)).get().getTurrets().size(); i++) {
									if (gm.getFloors().at(floor(vector.iterator / 5)).get().getTurrets().at(i).getSlot() ==
										((vector.iterator % 5) + 1)) {//Find the Turret that matches the slot number of the turret/consumable upgrade square
										gm.getFloors().at(floor(vector.iterator / 5)).get().delete_turret(i);//Delete that Turret based on i
										break;
									}
								}
								goBack = true;
							}
							else if (type == "upgradeConsumable") {//If we want to sell a Consumable, same procedure as Turret
								gm.getPlayer().setMoney(
									getUpgrade(vector.clicked_vector.at(vector.iterator)->getConsumable().getName(),
										vector.clicked_vector.at(vector.iterator)->getConsumable().getLevel()).cost * 0.8);
								for (std::size_t i = 0; i < gm.getFloors().at(floor(vector.iterator / 5)).get().getConsumables().size(); i++) {
									if (gm.getFloors().at(floor(vector.iterator / 5)).get().getConsumables().at(i).getSlot() ==
										(((vector.iterator % 5) + 1)) % 3) {
										gm.getFloors().at(floor(vector.iterator / 5)).get().delete_consumable(i);
										break;
									}
								}
								goBack = true;
							}
						}
					}
				}
			}
		}
	}
}

//Draws the information boxes for the Turrets, Firearms, and Consumables
//	Each object writes its own name and a special description
//	and activates specific bool tags that allow later lines of code
//	to add the relevant information to the info box
//	like a Wall doesn't need to display the damage it can deal but does
//	need to display its hp, something Firearms do not need to do
//	
//	The drawPurchase exists so that only when you click on an item to buy first
//	will a purchase option appear.
void draw_info_box(GameManager& gm, std::string name, std::vector<std::shared_ptr<Clickable>>& menu) {
	std::stringstream description;
	sf::Vector2f mousePos;
	bool hp, ROF, damage, punch, drawPurchase;
	hp = ROF = damage = punch = drawPurchase = false;
	int font_size = 30;

	menu.erase(menu.end() - 1, menu.end());
	stats info = getUpgrade(name, 1);
	//Start Turrets
	if (name == "Peashooter") {
		description << "Name: Peashooter\nDescription: A basic turret. Great for doing a \nlittle extra DPS";
		damage = ROF = punch = true;
		font_size = 20;
		drawPurchase = true;
	}
	else if (name == "Heavy Machine Gun") {
		description << "Name: Heavy Machine Gun\nDescription: ";
		damage = ROF = punch = true;
		font_size = 25;
		drawPurchase = true;
	}
	else if (name == "Tachanka") {
		description << "Name: Tachanka\nDescrition: Caution! Big meme ahead.";
		damage = ROF = punch = true;
		font_size = 27;
		drawPurchase = true;
	}
	else if (name == "Railgun") {
		description << "Name: Railgun\nDescription: High damage, high pierce\nwhat's not to love?";
		damage = ROF = punch = true;
		font_size = 25;
		drawPurchase = true;
	}
	else if (name == "Lazer Turret") {
		description << "Name: Lazer Turret\nDescription: IMMA FIRIN MAH LAZER!";
		damage = ROF = punch = true;
		font_size = 27;
		drawPurchase = true;
	}//End Turrets
	//Start Player Weapons
	else if (name == "Pistol") {
		description << "Name: Pistol\nDescription: Hold it at at 90 degree\nangle for extra damage!.";
		font_size = 25;
		damage = ROF = punch = true;
		drawPurchase = true;
	}
	else if (name == "Sniper") {
		description << "Name: Sniper\nDescription: No, you can not quickscope\nwith this. Sorry.";
		font_size = 23;
		damage = ROF = punch = true;
		drawPurchase = true;
	}
	else if (name == "Cat Gun") {
		description << "Name: Cat Gun\nDescription: while(true)\n{cout<<nyan<<endl;}";
		font_size = 25;
		damage = ROF = punch = true;
		drawPurchase = true;
	}
	else if (name == "Minigun") {
		description << "Name: Minigun\nDescription: It costs $400,000 to fire\nthis for twelve seconds (not really).";
		font_size = 25;
		damage = ROF = punch = true;
		drawPurchase = true;
	}
	else if (name == "Needler") {
		description << "Name:  Needler\nDescription: The Pink Death";
		font_size = 25;
		damage = ROF = punch = true;
		drawPurchase = true;
	}//End Player Guns
	 //Begin Consumables
	else if (name == "Mine") {
		description << "Name: Mine\nDescription: You buy mine.\nEnemy steps on mine.\nEnemy die.";
		damage = true;
		font_size = 30;
		drawPurchase = true;
	}
	else if (name == "Wall") {
		description << "Name: Wall\nDescription: Build a Wall he said.\nIt'll be fun he said.";
		font_size = 30;
		hp = true;
		drawPurchase = true;
	}
	else if (name == "Bandit Wire") {
		description << "Name: Bandit Wire\nDescription: Enemies are in for a 'Shock'.\nDeals damage when enemies walk through";
		damage = true;
		font_size = 23;
		drawPurchase = true;
	}
	else if (name == "Buzzsaw") {
		description << "Name: Buzzsaw\nDescription: It's generally a bad idea\nto walk into one of these.\nWill be destroyed overtime";
		damage = hp = true;
		font_size = 23;
		drawPurchase = true;
	}
	else if (name == "Gulper") {
		description << "Name: Gulper\nDescription: Swallows an enemy whole.\nLike a mine, but more chomppy";
		damage = true;
		font_size = 25;
		drawPurchase = true;
	}//End Consumables
	//Add the additional tags needed for the object
	if (damage) {
		description << "\nDamage: " << info.damage;
	}
	if (punch) {
		description << "\nPunch: " << info.punch;
	}
	if (ROF) {
		description << "\nRate of Fire: " << info.ROF << " Rounds per Minute";
	}
	if (hp) {
		description << "\nHealth: " << info.hp;
	}
	if (drawPurchase) {//If a purchase option needs to be drawn
		description << "\nCost: $" << info.cost;
		menu.push_back(std::make_shared<Clickable>(Clickable(50, 450, 800, 268, description.str(), gm.getFont(), font_size)));//description bounding box
		menu.push_back(std::make_shared<Clickable>(Clickable(580, 655, 200, 50, "Purchase", gm.getFont(), 25)));//purchase button box
	}
	else {//Else simply draw an empty info box
		menu.push_back(std::make_shared<Clickable>(Clickable(50, 450, 800, 268,"", gm.getFont(), font_size)));//description bounding box
	}
	//Display the box to the screen
	draw_boxes(menu, gm.getWindow());
	gm.getWindow().display();
}

//Determines if you can purchase the item based on name
//	Simply calls the other canPurchase after retrieving
//	the information from info.cpp
bool canPurchase(GameManager& gm, std::string item) {
	stats info = getStats(item);
	return canPurchase(gm, info.cost);
}

//Determines if you can purchase something based on cost
bool canPurchase(GameManager& gm, int cost) {
	if (gm.getPlayer().getMoney() >= cost) {//If you can
		gm.getPlayer().setMoney(-cost);//Deduct the amount
		return true;
	}
	else {
		bool goBack = false;
		sf::Vector2f mousePos;
		std::vector<std::shared_ptr<Clickable>> menu;
		menu.push_back(std::make_shared<Clickable>(Clickable(//Create a menu saying that you need more money to purchase the object
			gm.getWindow().getSize().x / 2 - 200, gm.getWindow().getSize().y / 2 - 150, 400, 300, "You require\nmore minerals\n(AKA Money)", gm.getFont(), 25)));
		menu.push_back(std::make_shared<Clickable>(Clickable(585, 450, 100, 50, "Okay", gm.getFont(), 20)));

		//Begin Player Input Checking---------------------------
		sf::Event event;
			while (gm.getWindow().isOpen() && !goBack) {
				draw_boxes(menu, gm.getWindow());
				gm.getWindow().display();
				//Poll for a mouse click
				while (gm.getWindow().pollEvent(event)) {
					if (event.type == sf::Event::Closed) {
						gm.getWindow().close();
					}
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
						mousePos = gm.getWindow().mapPixelToCoords(sf::Mouse::getPosition(gm.getWindow()));
						//If the mouse clicked on a Clickable
						if (clicked_on_menu(mousePos, menu)) {
							std::size_t selected_menu = getClickedMenu(mousePos, menu);
							//If the Clickable's function is to accept
							if (menu[selected_menu]->getFunction() == "Okay") {
								goBack = true;
							}
						}
					}
				}
			}
		return false;
	}
}

//Draws the player arsenal screen
void draw_player_menu(GameManager& gm) {
	std::vector<std::shared_ptr<Clickable>> construct;
	sf::Vector2f mousePos;
	std::string can_purchase;
	std::stringstream stream;
	stream << "Money\n" << gm.getPlayer().getMoney();
	bool goBack = false;

	construct.push_back(std::make_shared<Clickable>(Clickable(50, 50, 1180, 668, "", gm.getFont(), 0)));//menu background
	construct.push_back(std::make_shared<Clickable>(Clickable(50, 450, 1180, 268, "", gm.getFont(), 0)));//lower third bounding box
	construct.push_back(std::make_shared<Clickable>(Clickable(50, 450, 800, 268, "", gm.getFont(), 0)));//description bounding box
	construct.push_back(std::make_shared<Clickable>(Clickable(100, 75, 1080, 50, "Pistol", gm.getFont(), 40)));//Gun 1
	construct.push_back(std::make_shared<Clickable>(Clickable(100, 150, 1080, 50, "Sniper", gm.getFont(), 40)));//Gun 2
	construct.push_back(std::make_shared<Clickable>(Clickable(100, 225, 1080, 50, "Cat Gun", gm.getFont(), 40)));// Gun 3
	construct.push_back(std::make_shared<Clickable>(Clickable(100, 300, 1080, 50, "Minigun", gm.getFont(), 40)));//Gun 4
	construct.push_back(std::make_shared<Clickable>(Clickable(100, 375, 1080, 50, "Needler", gm.getFont(), 40)));//Gun 5

	construct.push_back(std::make_shared<Clickable>(Clickable(1050, 593, 125, 70, "Go\nBack", gm.getFont(), 25)));//Back menu
	construct.push_back(std::make_shared<Clickable>(Clickable(900, 593, 125, 70, stream.str(), gm.getFont(), 25)));//Money
	stream.str(std::string());
	stream << "\nLoadout:\n" << gm.getPlayer().getEquipped().getName() << "\n" << gm.getPlayer().getHolstered().getName();
	construct.push_back(std::make_shared<Clickable>(Clickable(900, 475, 275, 100, stream.str(), gm.getFont(), 20)));//Currently Equipped Weapons
	construct.push_back(std::make_shared<Clickable>(Clickable(0, 0, 0, 0, "", gm.getFont(), 0)));//Burner
	construct.push_back(std::make_shared<Clickable>(Clickable(0, 0, 0, 0, "", gm.getFont(), 0)));//Burner

	//Begin Player Input Checking---------------------------
	sf::Event event;
	while (gm.getWindow().isOpen() && !goBack) {//go back not true
		draw_boxes(construct, gm.getWindow());
		gm.getWindow().display();
		while(gm.getWindow().pollEvent(event)){
			if (event.type == sf::Event::Closed) {
				gm.getWindow().close();
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			mousePos = gm.getWindow().mapPixelToCoords(sf::Mouse::getPosition(gm.getWindow()));
			if (clicked_on_menu(mousePos, construct)) {
				std::size_t selected_menu = getClickedMenu(mousePos, construct);
				if (construct[selected_menu]->getFunction() == "Go\nBack") {
					goBack = true;
				}
				else if (construct[selected_menu]->getFunction() == "Purchase") {
					if (confirm(gm)) {
						if (canPurchase(gm, can_purchase)) {
							gm.purchaseGun(can_purchase);
							goBack = true;
						}
					}
				}
				else if (construct[selected_menu]->getFunction() == "Upgrade") {
					std::vector<std::shared_ptr<Clickable>> temp;
					draw_upgrade_menu(gm, can_purchase, clicked(temp, std::size_t(0)));
					goBack = true;
				}
				else if (construct[selected_menu]->getFunction() == "Equip") {
					draw_equip_menu(gm, gm.getGun(can_purchase));
					goBack = true;
				}
				else {//If the selected option is one of the Firearms
					can_purchase = construct[selected_menu]->getFunction();
					if (gm.hasPurchasedGun(can_purchase)){//If you have purchased the gun
						draw_weapon_equip(gm, can_purchase, construct);//Draw an info box with an equip/upgrade menu
					}
					//This checks if you have not purchased the gun and the menu you clicked was not just empty space
					else if(!gm.hasPurchasedGun(can_purchase) && can_purchase != " "){//Else draw an info box with a purchase menu
						draw_info_box(gm, can_purchase, construct);
					}
				}
			}
		}
	}
}

//Draw the equp/upgrade buttons
void draw_weapon_equip(GameManager& gm, std::string name, std::vector<std::shared_ptr<Clickable>>& menu) {
	bool goBack = false;
	sf::Vector2f mousePos;
	draw_info_box(gm, name, menu);
	menu.push_back(std::make_shared<Clickable>(Clickable(580, 655, 200, 50, "Equip", gm.getFont(), 20)));//equip button box
	menu.push_back(std::make_shared<Clickable>(Clickable(380, 655, 200, 50, "Upgrade", gm.getFont(), 25)));//upgrade button box
}

//Draws the menu where the player can equip a Firearm to the active or holstered slot
void draw_equip_menu(GameManager& gm, Firearm& firearm) {
	sf::Vector2f mousePos = gm.getWindow().mapPixelToCoords(sf::Mouse::getPosition(gm.getWindow()));
	std::size_t confirmation_choice;
	bool goBack = false;
	std::vector<std::shared_ptr<Clickable>> confirm_menu;
	confirm_menu.push_back(std::make_shared<Clickable>(Clickable(gm.getWindow().getSize().x / 2 - 200, gm.getWindow().getSize().y / 2 - 150, 400, 300, "Which slot?", gm.getFont(), 30)));
	confirm_menu.push_back(std::make_shared<Clickable>(Clickable(gm.getWindow().getSize().x / 2 - 175, gm.getWindow().getSize().y / 2 + 50, 150, 50, "Active", gm.getFont(), 25)));
	confirm_menu.push_back(std::make_shared<Clickable>(Clickable(gm.getWindow().getSize().x / 2 + 25, gm.getWindow().getSize().y / 2 + 50, 150, 50, "Holstered", gm.getFont(), 15)));
	confirm_menu.push_back(std::make_shared<Clickable>(Clickable(gm.getWindow().getSize().x / 2 - 100, 300, 200, 50, "Go Back", gm.getFont(), 30)));

	//Begin Player Input Checking---------------------------
	sf::Event event;
	while (gm.getWindow().isOpen() && !goBack) {
		draw_boxes(confirm_menu, gm.getWindow());
		gm.getWindow().display();
		while (gm.getWindow().pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				gm.getWindow().close();
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				sf::Vector2f mousePos = gm.getWindow().mapPixelToCoords(sf::Mouse::getPosition(gm.getWindow()));
				if (clicked_on_menu(mousePos, confirm_menu)) {
					confirmation_choice = getClickedMenu(mousePos, confirm_menu);
					if (confirm_menu[confirmation_choice]->getFunction() == "Active") {
						gm.getPlayer().swap_equipped(firearm);
						goBack = true;
					}
					else if (confirm_menu[confirmation_choice]->getFunction() == "Holstered") {
						gm.getPlayer().swap_holstered(firearm);
						goBack = true;
					}
					else if (confirm_menu[confirmation_choice]->getFunction() == "Go Back") {
						goBack = true;
					}
				}
			}
		}
	}
}

//Repairs the consumable to full health for a cost
void repair_consumable(GameManager& gm, clicked vector) {
	float repairPercent = 0.2;//The percentage cost to repair something
	std::vector<std::shared_ptr<Clickable>> construct;
	bool goBack = false;

	//If the consumable is active, it doesn't need to be repaired as it will be repaired for free during loading
	if(vector.clicked_vector.at(vector.iterator)->getConsumable().isActive()){
		construct.push_back(std::make_shared<Clickable>(Clickable(gm.getWindow().getSize().x / 2 - 200, gm.getWindow().getSize().y / 2 - 150, 400, 300, "This doesn't need\nrepairs", gm.getFont(), 25)));
		construct.push_back(std::make_shared<Clickable>(Clickable(585, 450, 100, 50, "Okay", gm.getFont(), 20)));

		//Begin Player Input Checking---------------------------
		sf::Event event;
		sf::Vector2f mousePos;
		while (gm.getWindow().isOpen() && !goBack) {
			draw_boxes(construct, gm.getWindow());
			gm.getWindow().display();
			while (gm.getWindow().pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					gm.getWindow().close();
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					mousePos = gm.getWindow().mapPixelToCoords(sf::Mouse::getPosition(gm.getWindow()));
					if (clicked_on_menu(mousePos, construct)) {
						std::size_t selected_menu = getClickedMenu(mousePos, construct);
						if (construct[selected_menu]->getFunction() == "Okay") {
							goBack = true;
						}
					}
				}
			}
		}//Wait, one more loop below!----------------------------
	}
	else {//If it does need repairs
		std::stringstream stream;
		stats info = getUpgrade(vector.clicked_vector.at(vector.iterator)->getConsumable().getName(), vector.clicked_vector.at(vector.iterator)->getConsumable().getLevel());
		stream << "Repair Costs:\n"<<info.cost * repairPercent;
		construct.push_back(std::make_shared<Clickable>(Clickable(gm.getWindow().getSize().x / 2 - 200, gm.getWindow().getSize().y / 2 - 150, 400, 300, stream.str(), gm.getFont(), 30)));
		construct.push_back(std::make_shared<Clickable>(Clickable(gm.getWindow().getSize().x / 2 - 150, gm.getWindow().getSize().y / 2 + 50, 100, 50, "Repair", gm.getFont(), 22)));
		construct.push_back(std::make_shared<Clickable>(Clickable(gm.getWindow().getSize().x / 2 + 50, gm.getWindow().getSize().y / 2 + 50, 100, 50, "Nope", gm.getFont(), 25)));

		//Begin Player Input Checking---------------------------
		sf::Event event;
		sf::Vector2f mousePos;
		while (gm.getWindow().isOpen() && !goBack) {
			draw_boxes(construct, gm.getWindow());
			gm.getWindow().display();
			while (gm.getWindow().pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					gm.getWindow().close();
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					mousePos = gm.getWindow().mapPixelToCoords(sf::Mouse::getPosition(gm.getWindow()));
					if (clicked_on_menu(mousePos, construct)) {
						std::size_t selected_menu = getClickedMenu(mousePos, construct);
						if (construct[selected_menu]->getFunction() == "Repair") {
							gm.getPlayer().setMoney(-info.cost * repairPercent);//Deduct the repair costs
							vector.clicked_vector.at(vector.iterator)->getConsumable().reload();//Reload the consumable
							goBack = true;
						}
						else if (construct[selected_menu]->getFunction() == "Nope") {
							goBack = true;
						}
					}
				}
			}
		}
	}
}
