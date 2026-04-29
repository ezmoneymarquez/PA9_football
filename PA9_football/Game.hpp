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
#include <map>
#include <string>

// Runs the 
class Game {
private:
    bool playStarted = false;
    bool ballSnapped = false;
	bool spaceHeldLastFrame = false;

    sf::RenderWindow window;

	std::map<std::string, sf::Texture> textures;

	sf::Texture qbTexture;
	sf::Texture receiver1Texture;
	sf::Texture receiver2Texture;
    sf::Texture oLineTexture;
    sf::Texture dLineTexture;
	sf::Texture defender1Texture;
	sf::Texture defender2Texture;
	sf::Texture ballTexture;
	sf::Texture fieldTexture;

    // Players
    Player qb;
    Player receiver1;
    Player receiver2;
	Player oLine1;
	Player dLine1;
    Player defender1;
    Player defender2;

    Ball ball;
    Endzone endZone;

    Field field;

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

void clamp(sf::Sprite& s);