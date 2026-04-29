/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*	Programmers: Josh Marquez, Iyke Odum												 *
*	Class: CptS 122, Spring 2026  Lab Section 1											 *
*	Programming Assignment: PA 9 2D Football Game Application							 *
*	Date: April 27, 2026																 *
*	Description: This program runs a simple 2D football game.							 *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once

#include <SFML/Graphics.hpp>

// Base class for all objects on ths screen
class Entity {
public:
    sf::Sprite sprite; // Image of the object
    sf::Vector2f velocity; // speed and direction of the object
    Entity(const sf::Vector2f& position)
        : velocity(0.f, 0.f)
    {
        sprite.setPosition(position);
    }

    // Optional: allow default too (recommended)
    Entity() : Entity({ 0.f, 0.f }) {}

    virtual ~Entity() {}

    // update function runs at every frame and updates the posistion of the object
    virtual void update(float dt) {
        sprite.move(velocity * dt);
    }

    // draws the object on the screen
    virtual void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

    // used to check that the object is still in the render window
    sf::FloatRect getBounds() const {
        return sprite.getGlobalBounds();
    }
};