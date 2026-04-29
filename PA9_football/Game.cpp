#include "Game.hpp"
#include <cmath>

Game::Game()
    : window(sf::VideoMode({ 800, 600 }), "2D Football"),
    qb(Position::Quarterback, textures["qb"]),
    receiver(Position::WideReceiver, textures["receiver"]),
    defender(Position::DefensiveBack, textures["defender"]),
    ball(sf::Vector2f( 100.f, 300.f ), textures["ball"]),
    endZone({ 750.f, 0.f }, { 50.f, 600.f })
{
    // Load textures
    qbTexture.loadFromFile("textures/american_football_player_sprite.png");
    receiverTexture.loadFromFile("textures/american_football_player_sprite.png");
    defenderTexture.loadFromFile("textures/american_football_player_sprite.png");
    ballTexture.loadFromFile("textures/football.png");
    
    
    qb.sprite.setTexture(qbTexture);
    receiver.sprite.setTexture(receiverTexture);
    defender.sprite.setTexture(defenderTexture);
    ball.sprite.setTexture(ballTexture);

    
    // Initial positions
    qb.sprite.setPosition({ 100.f, 300.f });
    receiver.sprite.setPosition({ 200.f, 200.f });
    defender.sprite.setPosition({ 500.f, 300.f });
    ball.sprite.setPosition({ 100.f, 300.f });

    // Resizing
	qb.sprite.setScale({ 3.f, 3.f });
	receiver.sprite.setScale({ 3.f, 3.f });
	defender.sprite.setScale({ 3.f, 3.f });
	ball.sprite.setScale({ 3.f, 3.f });

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

        ball.throwBall(dir, 400.f);
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

    qb.draw(window);
    receiver.draw(window);
    defender.draw(window);
    ball.draw(window);
    endZone.draw(window);

    window.display();
}