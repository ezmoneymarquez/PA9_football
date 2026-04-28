/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*	Programmers: Josh Marquez, Iyke Odum												 *
*	Class: CptS 122, Spring 2026  Lab Section 1											 *
*	Programming Assignment: PA 9 2D Football Game Application							 *
*	Date: April 27, 2026																 *
*	Description: This program runs a simple 2D football game.							 *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
#include "Player.hpp"
#include <SFML/Graphics.hpp>

class Endzone
{
private:
	sf::RectangleShape area;

public:
	Endzone(const sf::Vector2f& position, const sf::Vector2f& size);

	bool checkTD(const Player& player) const;
	void draw(sf::RenderWindow& window) const;
};
