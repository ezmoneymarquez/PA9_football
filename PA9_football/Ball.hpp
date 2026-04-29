/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*	Programmers: Josh Marquez, Iyke Odum												 *
*	Class: CptS 122, Spring 2026  Lab Section 1											 *
*	Programming Assignment: PA 9 2D Football Game Application							 *
*	Date: April 27, 2026																 *
*	Description: This program runs a simple 2D football game.							 *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
#include "Entity.hpp"

class Player;

class Ball : public Entity
{
public:
	Player* ballcarrier = nullptr;

	Ball(const sf::Vector2f& position, const sf::Texture texture)
		: Entity(position, texture), ballcarrier(nullptr)
	{}

	// Optional default
	Ball() : Ball({ 0.f, 0.f }) {}

	void update(float dt) override;
	void receiveBall(Player* player); // This function is called when a player receives the ball. It sets the ballcarrier to the player who received the ball.
	void throwBall(const sf::Vector2f& direction, float force); // This function is called when the ballcarrier throws the ball. It sets the ballcarrier to nullptr, indicating that the ball is now in the air and not being carried by any player.
};