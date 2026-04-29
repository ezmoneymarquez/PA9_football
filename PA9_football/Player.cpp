/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*	Programmers: Josh Marquez, Iyke Odum												 *
*	Class: CptS 122, Spring 2026  Lab Section 1											 *
*	Programming Assignment: PA 9 2D Football Game Application							 *
*	Date: April 27, 2026																 *
*	Description: This program runs a simple 2D football game.							 *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "Player.hpp"
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>

Player::Player(Position pos, sf::Texture& texture) : position(pos), Entity(texture) {};

void Player::handleInput() {
    velocity = { 0.f, 0.f };

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        velocity.y = -speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        velocity.y = speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        velocity.x = -speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        velocity.x = speed;
}

void Player::update(float dt) {
    handleInput();
    Entity::update(dt);
}

bool Player::isOffense() const
{
    return position == Position::Quarterback || position == Position::RunningBack ||
        position == Position::WideReceiver || position == Position::WideReceiver ||
        position == Position::TightEnd || position == Position::OffensiveLineman;
}

bool Player::isDefense() const
{
    return !isOffense();
}

bool Player::canThrow() const
{
    return position == Position::Quarterback && hasBall;
}

void Player::runRoute(float dt)
{
    if (position != Position::WideReceiver)
        return;

    sf::Vector2f pos = sprite.getPosition();
    sf::Vector2f dir = target - pos;

    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (len > 1.f)
    {
        dir /= len;
        velocity = dir * 150.f;
    }
    else
        velocity = { 0.f, 0.f };

    Entity::update(dt);
}

void Player::chase(const Player& target, float dt)
{
    if (!isDefense())
        return;

    sf::Vector2f pos = sprite.getPosition();
    sf::Vector2f dir = target.sprite.getPosition() = pos;

    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (len > 1.f)
    {
        dir /= len;
        velocity = dir * 180.f;
    }
    Entity::update(dt);
}

bool Player::isTackling(const Player& other) const
{
    return getBounds().findIntersection(other.getBounds()).has_value();
}