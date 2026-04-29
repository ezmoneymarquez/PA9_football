/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*	Programmers: Josh Marquez, Iyke Odum												 *
*	Class: CptS 122, Spring 2026  Lab Section 1											 *
*	Programming Assignment: PA 9 2D Football Game Application							 *
*	Date: April 27, 2026																 *
*	Description: This program runs a simple 2D football game.							 *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#pragma once

class GameState {
public:
    // Core football rules
    int down;
    float yardsToGo;
    float ballX;

    // Trackings
    float startX;

    // Score
    int score;

    GameState();


    void startNewDrive(float startPosition);
    void startNewPlay(float currentBallPos);

    void updateBallPosition(float newX);

    // Returns true if first down achieved
    bool checkFirstDown(float gainedYards);

    // Returns true if turnover on downs
    bool checkTurnover();

    // Returns yards gained in play
    float getYardsGained() const;

    // Updates the score, down, and yards to go if there is a touchdown
    void addTouchdown();
};