/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*	Programmers: Josh Marquez, Iyke Odum												 *
*	Class: CptS 122, Spring 2026  Lab Section 1											 *
*	Programming Assignment: PA 9 2D Football Game Application							 *
*	Date: April 27, 2026																 *
*	Description: This program runs a simple 2D football game.							 *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "Ball.hpp"
#include "Player.hpp"
#include <cmath>

static sf::Vector2f normalize(const sf::Vector2f& v)
{
	float length = std::sqrt(v.x * v.x + v.y * v.y);
	if (length != 0.f)
		return v / length;
	return { 0.f, 0.f };
}

void Ball::update(float dt)
{
	if (ballcarrier != nullptr)
	{
		sf::Vector2f playerPos = ballcarrier->sprite.getPosition();
		sprite.setPosition({ playerPos.x + 20.f, playerPos.y });
		velocity = { 0.f, 0.f };
	}
	else
	{
		velocity *= 0.98f;
		if (std::abs(velocity.x) < 0.01f)
			velocity.x = 0.f;
		if (std::abs(velocity.y) < 0.01f)
			velocity.y = 0.f;

		Entity::update(dt);
	}
}

void Ball::receiveBall(Player* player)
{
	ballcarrier = player;
	if (player)
		player->hasBall = true;
}

void Ball::throwBall(const sf::Vector2f& direction, float force)
{
	if (!ballcarrier)
		return;

	ballcarrier->hasBall = false;
	ballcarrier = nullptr;

	sf::Vector2f dir = direction;
	float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
	if (len != 0)
		dir /= len;

	velocity = dir * force;
}