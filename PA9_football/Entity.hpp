#pragma once

#include <SFML/Graphics.hpp>

// Base class for all objects on ths screen
class Entity {
public:
    sf::Sprite sprite; // Image of the object
    sf::Vector2f velocity; // speed and direction of the object

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