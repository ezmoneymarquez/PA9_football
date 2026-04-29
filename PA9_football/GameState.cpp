#include "GameState.hpp"

GameState::GameState()
    : down(1),
    yardsToGo(10.f),
    ballX(100.f),
    startX(100.f),
    score(0)
{
}

void GameState::startNewDrive(float startPosition) {
    down = 1;
    yardsToGo = 10.f;
    ballX = startPosition;
    startX = startPosition;
}

void GameState::startNewPlay(float currentBallPos) {
    startX = currentBallPos;
}

void GameState::updateBallPosition(float newX) {
    ballX = newX;
}

float GameState::getYardsGained() const {
    return ballX - startX;
}

bool GameState::checkFirstDown(float gainedYards) {
    if (gainedYards >= yardsToGo) {
        down = 1;
        yardsToGo = 10.f;
        return true;
    }
    return false;
}

bool GameState::checkTurnover() {
    if (down > 4) {
        down = 1;
        yardsToGo = 10.f;
        return true;
    }
    return false;
}

void GameState::addTouchdown() {
    score += 7;
    down = 1;
    yardsToGo = 10.f;
}