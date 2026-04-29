#include "Game.hpp"
#include <iostream>
#include <cmath>

Game::Game()
    : window(sf::VideoMode({ 800, 600 }), "2D Football"),
    qbTexture("Textures/american_football_player_sprite.png"),
	receiverTexture("Textures/american_football_player_sprite.png"),
	defenderTexture("Textures/american_football_player_sprite.png"),
    ballTexture("Textures/Football.png"),
    fieldTexture("Textures/Field.png"),
    qb(Position::Quarterback, qbTexture),
    receiver(Position::WideReceiver, receiverTexture),
    defender(Position::DefensiveBack, defenderTexture),
    ball(sf::Vector2f( 100.f, 300.f ), ballTexture),
    endZone({ 700.f, 0.f }, { 100.f, 600.f }),
    field(fieldTexture)
{
    //// Load textures
    //qbTexture.loadFromFile("Textures/american_football_player_sprite.png");
    //receiverTexture.loadFromFile("Textures/american_football_player_sprite.png");
    //defenderTexture.loadFromFile("Textures/american_football_player_sprite.png");
    //ballTexture.loadFromFile("Textures/football.png");
    //
    //
    //qb.sprite.setTexture(qbTexture);
    //receiver.sprite.setTexture(receiverTexture);
    //defender.sprite.setTexture(defenderTexture);
    //ball.sprite.setTexture(ballTexture);

    
    // Initial positions
    qb.sprite.setPosition({ 100.f, 300.f });
    receiver.sprite.setPosition({ 200.f, 200.f });
    defender.sprite.setPosition({ 500.f, 300.f });
    ball.sprite.setPosition({ 100.f, 300.f });
	field.sprite.setPosition({ 0.f, 0.f });

    // Resizing
	qb.sprite.setScale({ .15f, .15f });
	receiver.sprite.setScale({ .15f, .15f });
	defender.sprite.setScale({ .15f, .15f });
	ball.sprite.setScale({ .03f, .03f });
	field.sprite.setScale({ .25f, .20f });

    ball.receiveBall(&qb);
}

void Game::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        processEvents();
        update(dt);
        render();
    }
}

void Game::processEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            window.close();
    }
}

void Game::handleInput() {
    qb.velocity = { 0.f, 0.f };

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        qb.velocity.y = -200.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        qb.velocity.y = 200.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        qb.velocity.x = -200.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        qb.velocity.x = 200.f;

    // Throw
    if (qb.canThrow() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        sf::Vector2f dir = qb.velocity;

        if (dir == sf::Vector2f(0.f, 0.f))
            dir = { 1.f, 0.f };

        ball.throwBall(dir, 4000.f);
    }
}

void Game::update(float dt) {
    handleInput();

    qb.update(dt);

    // Receiver runs route
    receiver.target = { 700.f, 200.f };
    receiver.runRoute(dt);

    // Defender chases ball carrier
    Player* target = ball.ballcarrier ? ball.ballcarrier : &receiver;
    defender.chase(*target, dt);

    ball.update(dt);

    checkCollisions();

    // Track yard progress
    if (ball.ballcarrier) {
        state.ballX = ball.ballcarrier->sprite.getPosition().x;
    }
}

void Game::checkCollisions() {
    // Catch ball
    if (ball.ballcarrier == nullptr &&
        receiver.getBounds().findIntersection(ball.getBounds()).has_value()) {
        ball.receiveBall(&receiver);
    }

    // Tackle
    if (ball.ballcarrier == &receiver &&
        defender.isTackling(receiver)) {
        endPlay(false);
    }

    // Touchdown
    if (ball.ballcarrier &&
        endZone.checkTD(*ball.ballcarrier)) {
        endPlay(true);
    }
}


void Game::endPlay(bool touchdown) {
    float gained = state.ballX - startX;

    if (touchdown) {
        state.down = 1;
        state.yardsToGo = 10.f;
    }
    else {
        if (gained >= state.yardsToGo) {
            state.down = 1;
            state.yardsToGo = 10.f;
        }
        else {
            state.yardsToGo -= gained;
            state.down++;
        }
    }

    // Reset positions
    qb.sprite.setPosition({ 100.f, 300.f });
    receiver.sprite.setPosition({ 200.f, 200.f });
    defender.sprite.setPosition({ 500.f, 300.f });
    ball.sprite.setPosition({ 100.f, 300.f });

    ball.receiveBall(&qb);

    startX = qb.sprite.getPosition().x;
}

//Draws all of the game assests on to the screen
void Game::render() {
    window.clear();

    endZone.draw(window);
    
    field.draw(window);
    
    qb.draw(window);
    receiver.draw(window);
    defender.draw(window);
    ball.draw(window);
    

    window.display();
}