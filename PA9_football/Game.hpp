/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*	Programmers: Josh Marquez, Iyke Odum												 *
*	Class: CptS 122, Spring 2026  Lab Section 1											 *
*	Programming Assignment: PA 9 2D Football Game Application							 *
*	Date: April 27, 2026																 *
*	Description: This program runs a simple 2D football game.							 *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Ball.hpp"
#include "EndZone.hpp"
#include "GameState.hpp"

// Runs the 
class Game {
private:
    sf::RenderWindow window;

    // Players
    Player qb;
    Player receiver;
    Player defender;

    Ball ball;
    Endzone endZone;

    GameState state;

    float startX = 0.f;

public:
    // Sets the initial postions for when the game starts
    Game();

    // Starts the clock and begins the main game loop
    void run();

private:
    
    //
    void processEvents();
    void update(float dt);
    void render();

    void handleInput();
    void checkCollisions();
    void endPlay(bool touchdown);
};