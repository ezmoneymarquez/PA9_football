/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*	Programmers: Josh Marquez, Iyke Odum												 *
*	Class: CptS 122, Spring 2026  Lab Section 1											 *
*	Programming Assignment: PA 9 2D Football Game Application							 *
*	Date: April 27, 2026																 *
*	Description: This program runs a simple 2D football game.							 *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#pragma once
#include "Entity.hpp"
#include "Position.hpp"

class Player : public Entity {
public:
    Position position;

    Player(Position pos);

    float speed = 200.f;
    bool hasBall = false;

    void handleInput(); // 
    void update(float dt) override;

    bool isOffense() const;
    bool isDefense() const;

    bool canThrow() const;
};