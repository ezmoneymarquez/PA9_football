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