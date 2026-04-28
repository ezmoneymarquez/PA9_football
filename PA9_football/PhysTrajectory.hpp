/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*	Programmers: Josh Marquez, Iyke Odum												 *
*	Class: CptS 122, Spring 2026  Lab Section 1											 *
*	Programming Assignment: PA 9 2D Football Game Application							 *
*	Date: April 27, 2026																 *
*	Description: This program runs a simple 2D football game.							 *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once

#include <SFML/System.hpp>

class PhysTrajectory
{
public:
	static void applyLinear(sf::Vector2f& position, sf::Vector2f& velocity, float dt);

	static void applyFriction(sf::Vector2f& velocity, float friction);

	static void applyGravity(sf::Vector2f& velocity, float gravity, float dt);

};
