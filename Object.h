#pragma once

#include "stdafx.h"

/* Object is everything in this game that is supposed to be seen by the player
 * texture holds the texture of the object
 * sprite allows the object's texture to be set to an origin and drawn to screen
 * spLength and spHeight save texture dimensions
 *		This is used in cases where other objects need to be aligned in reference to this object
 * x and y holds the origin cooridnates of the object on the display
 */
class Object {
	protected:
		sf::Texture texture;
		sf::Sprite sprite;
		int spLength;
		int spHeight;
		int x;
		int y;
	public:

		/*
		* Brief: Fuctions that return important landmark locations on the object
		* Param: Nothing
		* Return: A coordinate
		* Note: XR is the x-coordinate of the right edge
		*		YU is the y-coordinate of the top edge
		*		XL is the x-coodinate of left edge
		*		YD is the y-coordinate of the bottom edge
		*		YC is the y-coordinate of the center
		*/
		int getXR();
		int getYU();
		int getXL();
		int getYD();
		int getYC();

		/*
		* Brief: Getter for the sprite
		* Param: Nothing
		* Return: Reference to the object's sprite
		*/
		sf::Sprite& getSprite();

		/*
		* Brief: Setter for spHeight and spLength based on the texture
		* Param: A texture
		* Return: Nothing
		*/
		void setSpriteDimensions(sf::Texture texture_);
};