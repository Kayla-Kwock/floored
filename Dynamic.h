#pragma once

#include "stdafx.h"
/* Dynamic is any object that can move. These include Enemy, Projectile and Player
 * floor saves which floor the object is on
 * speed represents how fast the object moves. Higher numbers means faster motion
 * active represents if the object is active
 * dead represents if the object is dead
 * see below for additional details on active and dead
 *----------------------------------------------------------------------------------
 *	Active and Dead
 * These two are used together to represent the state of
 * an Enemy or a Projectile
 * If it is not active and not dead
 *	The object hasn't been spawned yet
 * If it is active and not dead
 *	The object is spawned and not dead
 * If it is active and dead
 *	The object has been spawned and killed
 * There should be no case in which it is not active and dead
 */

class Dynamic : public Object {
protected:
	int floor;
	float speed;
	bool active;
	bool dead;
public:

	/*
	* Brief: Sets the X-coordinate of the sprite's origin
	* Param: The x coordinate
	* Return: Nothing
	*/
	void setX(int XL);

	/*
	* Brief: Sets the Y-coordinate of the sprite's origin
	* Param: The y coordinate
	* Return: Nothing
	*/
	void setY(int YU);

	/*
	* Brief: Returns the object's movement speed
	* Param: Nothing
	* Return: A movement speed integer
	*/
	int getSpeed();

	/*
	* Brief: Returns what floor the object is on
	* Param: Nothing
	* Return: A floor number
	*/
	int getFloor();

	/*
	* Brief: Sets the floor the object is on
	* Param: A floor number
	* Return: Nothing
	*/
	void setFloor(int floor_);

	/*
	* Brief: Directional movements for the object
	* Param: A time from last frame update
	* Return: Nothing
	* Note: moveUp and moveDown are not in use but kept for completion's sake
	*/
	void moveRight(float delta);
	void moveLeft(float delta);
	void moveUp(float delta);
	void moveDown(float delta);
	
	/*
	* Brief: Moves object up and down floors
	* Param: Nothing
	* Return: Nothing
	* Note: Changes the object's floor and adjust its origin's y-coordinate
	* to match its new vertical position.
	*/
	void moveUpFloor();
	void moveDownFloor();

	/*
	* Brief: Getter and Setter for the active variable of an object
	* Param: Nothing and nothing
	* Return: If the object is active and nothing
	* Note: Used for Projectile and Enemy, used in tandem with Dead
	*/
	bool isActive();
	virtual void setActive();

	/*
	* Brief: Getters and Setter for the dead variable of an object
	* Param: Nothing, nothing, and nothing
	* Return: If the object is dead, is not dead, and nothing
	* Note: Used for Projectile and Enemy, used in tandem with Active
	*/
	bool isDead();
	bool isNotDead();
	void setDead();
};