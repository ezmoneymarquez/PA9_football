#include "Game.hpp"
#include <iostream>
#include <cmath>

Game::Game()
    : window(sf::VideoMode({ 800, 600 }), "2D Football"),
    qbTexture("Textures/american_football_player_sprite.png"),
	receiver1Texture("Textures/american_football_player_sprite.png"),
	receiver2Texture("Textures/american_football_player_sprite.png"),
	oLineTexture("Textures/american_football_player_sprite.png"),
	dLineTexture("Textures/american_football_player_sprite_white.png"),
	defender1Texture("Textures/american_football_player_sprite_white.png"),
	defender2Texture("Textures/american_football_player_sprite_white.png"),
    ballTexture("Textures/Football.png"),
    fieldTexture("Textures/Field.png"),
    qb(Position::Quarterback, qbTexture),
    receiver1(Position::WideReceiver, receiver1Texture),
    receiver2(Position::WideReceiver, receiver2Texture),
    oLine1(Position::OffensiveLineman, oLineTexture),
    dLine1(Position::DefensiveLineman, dLineTexture),
    defender1(Position::DefensiveBack, defender1Texture),
    defender2(Position::DefensiveBack, defender2Texture),
    ball(sf::Vector2f( 100.f, 300.f ), ballTexture),
    endZone({ 700.f, 0.f }, { 125.f, 600.f }),
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
    receiver1.sprite.setPosition({ 200.f, 200.f });
	receiver2.sprite.setPosition({ 200.f, 400.f });
	oLine1.sprite.setPosition({ 200.f, 250.f });
    dLine1.sprite.setPosition({ 475.f, 300.f });
    defender1.sprite.setPosition({ 500.f, 200.f });
	defender2.sprite.setPosition({ 500.f, 400.f });
    ball.sprite.setPosition({ 100.f, 300.f });
	field.sprite.setPosition({ 0.f, 0.f });

    // Resizing
	qb.sprite.setScale({ .15f, .15f });
	receiver1.sprite.setScale({ .15f, .15f });
	receiver2.sprite.setScale({ .15f, .15f });
	oLine1.sprite.setScale({ .15f, .15f });
	dLine1.sprite.setScale({ .15f, .15f });
	defender1.sprite.setScale({ .15f, .15f });
	defender2.sprite.setScale({ .15f, .15f });  
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

    Player* controlled = ball.ballcarrier ? ball.ballcarrier : &qb;

    controlled->velocity = { 0.f, 0.f };

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        controlled->velocity.y = -200.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        controlled->velocity.y = 200.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        controlled->velocity.x = -200.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        controlled->velocity.x = 200.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C))
        playStarted = true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
        playStarted = false;
    

    // Throw
    if (qb.canThrow() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        sf::Vector2f dir = qb.velocity;

        if (dir == sf::Vector2f(0.f, 0.f))
            dir = { 1.f, 0.f };

        ball.throwBall(dir, 4000.f);
    }
}

void Game::update(float dt) {

    /*bool spaceNow = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);

    if (spaceNow && !spaceHeldLastFrame)
    {
        if (!playStarted)
        {
            playStarted = true;
            ballSnapped = true;

            ball.receiveBall(&qb);
			state.startNewPlay(qb.sprite.getPosition().x);
        }
    }

    spaceHeldLastFrame = spaceNow;

	if (!playStarted)
        return;

    handleInput();

    qb.update(dt);
    receiver1.runRoute(dt);
	receiver2.runRoute(dt);

	Player* target = ball.ballcarrier ? ball.ballcarrier : &qb;
	defender1.chase(*target, dt);
	defender2.chase(*target, dt);

	ball.update(dt);

	if (defender1.getBounds().findIntersection(qb.getBounds()).has_value() || defender2.getBounds().findIntersection(qb.getBounds()).has_value())
    {
        playStarted = false;

        float gained = state.getYardsGained();

        if (!state.checkFirstDown(gained))
        {
			state.yardsToGo -= gained;
            state.down++;
        }
    }

   */

    handleInput();

    if (!playStarted)
        return;

    bool throwNow = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E);

    if (throwNow && !throwHeldLastFrame)
    {
        if (playStarted && ball.ballcarrier == &qb)
        {
            // choose receiver (simple: closest)
            Player* targetReceiver = &receiver1;

            float d1 = std::sqrt(std::pow(receiver1.sprite.getPosition().x - qb.sprite.getPosition().x, 2) + std::pow(receiver1.sprite.getPosition().y - qb.sprite.getPosition().y, 2));
			float d2 = std::sqrt(std::pow(receiver2.sprite.getPosition().x - qb.sprite.getPosition().x, 2) + std::pow(receiver2.sprite.getPosition().y - qb.sprite.getPosition().y, 2));

            if (d2 < d1)
                targetReceiver = &receiver2;

            sf::Vector2f dir =
                targetReceiver->sprite.getPosition() - qb.sprite.getPosition();

            ball.throwBall(dir, 28500.f);
			passInAir = true;
        }
    }

    throwHeldLastFrame = throwNow;

    if (!playStarted)
        return;

    qb.update(dt);

    // Receiver runs route
    receiver1.target = { 700.f, 200.f };
    receiver1.runRoute(dt);

	receiver2.target = { 700.f, 400.f };
    receiver2.runRoute(dt);

    // Defender chases ball carrier
    Player* target = ball.ballcarrier ? ball.ballcarrier : &qb;
    defender1.chase(*target, dt);
	defender2.chase(*target, dt);
	dLine1.chase(*target, dt);

    ball.update(dt);

    // ================= INCOMPLETE PASS =================
    if (passInAir && ball.ballcarrier == nullptr)
    {
        float speed = std::sqrt(ball.velocity.x * ball.velocity.x +
            ball.velocity.y * ball.velocity.y);

        // if ball slowed down enough → no catch → dead play
        if (speed < 20.f)
        {
            std::cout << "INCOMPLETE PASS\n";

            playStarted = false;
            passInAir = false;

            // update down (no yards gained)
            float gained = state.ballX - state.startX;

            if (!state.checkFirstDown(gained)) {
                state.yardsToGo -= gained;
                state.down++;
            }

            // reset positions
            qb.sprite.setPosition({ 100.f, 300.f });
            receiver1.sprite.setPosition({ 200.f, 200.f });
            receiver2.sprite.setPosition({ 200.f, 400.f });
            oLine1.sprite.setPosition({ 200.f, 250.f });
            dLine1.sprite.setPosition({ 475.f, 300.f });
            defender1.sprite.setPosition({ 500.f, 200.f });
            defender2.sprite.setPosition({ 500.f, 400.f });
            ball.sprite.setPosition({ 100.f, 300.f });

            ball.receiveBall(&qb);
        }
    }

    checkCollisions();

    // Track yard progress
    if (ball.ballcarrier) {
        state.ballX = ball.ballcarrier->sprite.getPosition().x;
    }

    clamp(qb.sprite);
    clamp(receiver1.sprite);
    clamp(receiver2.sprite);
    clamp(defender1.sprite);
    clamp(defender2.sprite);
    clamp(dLine1.sprite);
}

//void Game::checkCollisions() {
//    // Catch ball
//    if (ball.ballcarrier == nullptr &&
//        receiver1.getBounds().findIntersection(ball.getBounds()).has_value()) {
//        ball.receiveBall(&receiver1);
//    }
//
//    // Tackle
//    if (ball.ballcarrier == &receiver1 &&
//        defender1.isTackling(receiver1)) {
//        endPlay(false);
//    }
//
//    // Touchdown
//    if (ball.ballcarrier &&
//        endZone.checkTD(*ball.ballcarrier)) {
//        endPlay(true);
//    }
//}

void Game::checkCollisions()
{
    // Only if ball is in the air
    //if (ball.ballcarrier == nullptr)
    //{
    //    if (receiver1.getBounds().findIntersection(ball.getBounds()).has_value())
    //    {
    //        ball.receiveBall(&receiver1);
    //    }

    //    else if (receiver2.getBounds().findIntersection(ball.getBounds()).has_value())
    //    {
    //        ball.receiveBall(&receiver2);
    //    }

    //     // Touchdown
    //    if (ball.ballcarrier && endZone.checkTD(*ball.ballcarrier)) {
    //        endPlay(true);
    //        return;
    //    }
    //}

    if (ball.ballcarrier == nullptr) {
        auto ballPos = ball.sprite.getPosition();

        auto dist = [&](const Player& p) {
            sf::Vector2f d = p.sprite.getPosition() - ballPos;
            return d.x * d.x + d.y * d.y;  // squared distance, no sqrt needed
            };

        bool r1hit = receiver1.getBounds().findIntersection(ball.getBounds()).has_value();
        bool r2hit = receiver2.getBounds().findIntersection(ball.getBounds()).has_value();

        if (r1hit && r2hit)
        {
            ball.receiveBall(dist(receiver1) < dist(receiver2) ? &receiver1 : &receiver2);
			passInAir = false;  // Ball is no longer in the air after being caught
        }
        else if (r1hit)
        {
            ball.receiveBall(&receiver1);
			passInAir = false;  // Ball is no longer in the air after being caught
        }
        else if (r2hit)
        {
            ball.receiveBall(&receiver2);
			passInAir = false;  // Ball is no longer in the air after being caught
        }
    }

    // Tackle logic (whoever has ball)
    Player* carrier = ball.ballcarrier ? ball.ballcarrier : &qb;

	if ((ball.ballcarrier == &qb && (defender1.isTackling(qb) || defender2.isTackling(qb) || dLine1.isTackling(qb))) ||
        (ball.ballcarrier == &receiver1 && (defender1.isTackling(receiver1) || defender2.isTackling(receiver1) || dLine1.isTackling(receiver1))) ||
        (ball.ballcarrier == &receiver2 && (defender1.isTackling(receiver2) || defender2.isTackling(receiver2) || dLine1.isTackling(receiver2))))
    {
        endPlay(false);
    }

    // ================= TOUCHDOWN CHECK =================
    if (ball.ballcarrier)
    {
        if (endZone.checkTD(*ball.ballcarrier))
        {
            // Touchdown logic
            playStarted = false;

            std::cout << "TOUCHDOWN!\n";

            state.addTouchdown();

            // Reset play
            qb.sprite.setPosition({ 100.f, 300.f });
            receiver1.sprite.setPosition({ 200.f, 200.f });
            receiver2.sprite.setPosition({ 200.f, 400.f });
            oLine1.sprite.setPosition({ 200.f, 250.f });
            dLine1.sprite.setPosition({ 475.f, 300.f });
            defender1.sprite.setPosition({ 500.f, 200.f });
            defender2.sprite.setPosition({ 500.f, 400.f });
            ball.sprite.setPosition({ 100.f, 300.f });

            ball.receiveBall(&qb);

            state.startNewPlay(qb.sprite.getPosition().x);

            return; // stop further collision checks
        }
    }

    /*if (defender1.getBounds().findIntersection(carrier->getBounds()))
    {
        playStarted = false;

        float gained = state.ballX - state.startX;

        if (!state.checkFirstDown(gained)) {
            state.yardsToGo -= gained;
            state.down++;
        }
    }
    if (defender2.getBounds().findIntersection(carrier->getBounds()))
    {
        playStarted = false;

        float gained = state.ballX - state.startX;

        if (!state.checkFirstDown(gained)) {
            state.yardsToGo -= gained;
            state.down++;
        }
    }*/
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
    receiver1.sprite.setPosition({ 200.f, 200.f });
    receiver2.sprite.setPosition({ 200.f, 400.f });
    oLine1.sprite.setPosition({ 200.f, 250.f });
    dLine1.sprite.setPosition({ 475.f, 300.f });
    defender1.sprite.setPosition({ 500.f, 200.f });
    defender2.sprite.setPosition({ 500.f, 400.f });
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
    receiver1.draw(window);
    receiver2.draw(window);
    oLine1.draw(window);
    dLine1.draw(window);
    defender1.draw(window);
    defender2.draw(window);
    ball.draw(window);

    
    

    window.display();
}

void clamp(sf::Sprite& s)
{
    auto pos = s.getPosition();

    pos.x = std::max(0.f, std::min(800.f, pos.x));
	pos.y = std::max(0.f, std::min(600.f, pos.y));

	s.setPosition(pos);
}

//Test functions
void Game::runAllTests()
{
    std::cout << "Running Tests...\n";

    std::cout << "Snap Test: " << (testSnap() ? "PASS\n" : "FAIL\n");
    std::cout << "Throw/Catch Test: " << (testThrowCatch() ? "PASS\n" : "FAIL\n");
    std::cout << "Incomplete Pass Test: " << (testIncompletePass() ? "PASS\n" : "FAIL\n");
    std::cout << "Tackle Test: " << (testTackle() ? "PASS\n" : "FAIL\n");
    std::cout << "Touchdown Test: " << (testTouchdown() ? "PASS\n" : "FAIL\n");
}

bool Game::testSnap()
{
    playStarted = false;

    // simulate snap
    playStarted = true;

    return playStarted == true;
}

bool Game::testThrowCatch()
{
    // reset
    ball.receiveBall(&qb);
    playStarted = true;

    // place receiver in front
    receiver1.sprite.setPosition(qb.sprite.getPosition() + sf::Vector2f(50.f, 0.f));

    // throw
    sf::Vector2f dir = receiver1.sprite.getPosition() - qb.sprite.getPosition();
    ball.throwBall(dir, 300.f);

    // simulate updates
    for (int i = 0; i < 60; i++) {
        ball.update(0.016f);

        if (receiver1.getBounds().findIntersection(ball.getBounds())) {
            ball.receiveBall(&receiver1);
            break;
        }
    }

    return ball.ballcarrier == &receiver1;
}

bool Game::testIncompletePass()
{
    ball.receiveBall(&qb);
    playStarted = true;
    passInAir = true;

    // throw away from receivers
    sf::Vector2f dir = { 1.f, 0.f };
    ball.throwBall(dir, 300.f);

    bool incompleteDetected = false;

    for (int i = 0; i < 200; i++) {
        ball.update(0.016f);

        float speed = std::sqrt(ball.velocity.x * ball.velocity.x +
            ball.velocity.y * ball.velocity.y);

        if (speed < 20.f) {
            incompleteDetected = true;
            break;
        }
    }

    return incompleteDetected;
}

bool Game::testTackle()
{
    ball.receiveBall(&qb);
    playStarted = true;

    // force defender overlap
    defender1.sprite.setPosition(qb.sprite.getPosition());

    bool tackled = defender1.getBounds().findIntersection(qb.getBounds()).has_value();

    return tackled;
}

bool Game::testTouchdown()
{
    ball.receiveBall(&qb);
    playStarted = true;

    // move QB into endzone
    qb.sprite.setPosition({ 760.f, 300.f });

    bool td = endZone.checkTD(qb);

    return td;
}