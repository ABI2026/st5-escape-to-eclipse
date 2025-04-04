#include "Game.h"
#include <iostream>

const int screenWidth = 1920;
const int screenHeight = 1080;

const float rotationSpeed = 180.0f;
const float thrust = 50.0f;
const float boostMultiplier = 1.5f;
const float damping = 0.98f;
const float gravitationStrength = 1000.0f;
const float starMass = 1500.0f;
const float minDistance = 20.0f;

Game::Game(sf::RenderWindow& window) :
    window(window),
    state(MAIN_MENU),
    mainMenu(window),
    pauseMenu(window),
    settingsMenu(window) {

    initGame();
}

void Game::run() {
    while (window.isOpen() && state != EXIT) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        update();
        render();
    }
}

void Game::update() {
    switch (state) {
    case MAIN_MENU:
        mainMenu.update();
        handleMainMenuInput();
        break;

    case GAME_PLAY:
        handleGameplayInput();
        updateGame();
        break;

    case GAME_PAUSED:
        pauseMenu.update();
        handlePauseMenuInput();
        break;

    case SETTINGS:
        settingsMenu.update();
        handleSettingsMenuInput();
        break;

    default:
        break;
    }
}

void Game::render() {
    switch (state) {
    case MAIN_MENU:
        window.clear(sf::Color(30, 30, 30));
        mainMenu.render();
        break;

    case GAME_PLAY:
        renderGame();
        break;

    case GAME_PAUSED:
        renderGame();
        pauseMenu.render();
        break;

    case SETTINGS:
        window.clear(sf::Color(30, 30, 30));
        settingsMenu.render();
        break;

    default:
        break;
    }

    window.display();
}

void Game::handleMainMenuInput() {
    int option = mainMenu.handleInput();
    switch (option) {
    case MainMenu::START:
        state = GAME_PLAY;
        break;

    case MainMenu::SETTINGS:
        state = SETTINGS;
        break;

    case MainMenu::EXIT:
        state = EXIT;
        break;

    default:
        break;
    }
}

void Game::handlePauseMenuInput() {
    int option = pauseMenu.handleInput();
    switch (option) {
    case PauseMenu::RESUME:
        state = GAME_PLAY;
        deltaClock.restart();
        break;

    case PauseMenu::SETTINGS:
        state = SETTINGS;
        break;

    case PauseMenu::MAIN_MENU:
        state = MAIN_MENU;
        initGame();
        break;

    case PauseMenu::EXIT:
        state = EXIT;
        break;

    default:
        break;
    }
}

void Game::handleSettingsMenuInput() {
    int option = settingsMenu.handleInput();
    if (option == SettingsMenu::BACK) {
        state = (state == SETTINGS) ? MAIN_MENU : GAME_PAUSED;
    }
}

void Game::initGame() {
    if (!playerTexture.loadFromFile("Graphics/player.png")) {
        std::cerr << "Error: Could not load player texture!" << std::endl;
        state = EXIT;
        return;
    }

    if (!starTexture.loadFromFile("Graphics/star.png")) {
        std::cerr << "Error: Could not load star texture!" << std::endl;
        state = EXIT;
        return;
    }

    player.setSize(sf::Vector2f(50, 50));
    player.setOrigin(25, 25);
    player.setPosition(screenWidth / 2 + 200, screenHeight / 2);
    player.setTexture(&playerTexture);
    player.setRotation(-90);

    star.setRadius(50);
    star.setOrigin(50, 50);
    starPos = sf::Vector2f(screenWidth / 2, screenHeight / 2);
    star.setPosition(starPos);
    star.setTexture(&starTexture);

    borderRect.setSize(sf::Vector2f(screenWidth - 2 * borderPadding, screenHeight - 2 * borderPadding));
    borderRect.setPosition(borderPadding, borderPadding);
    borderRect.setFillColor(sf::Color::Transparent);
    borderRect.setOutlineColor(sf::Color(100, 100, 255, 100));
    borderRect.setOutlineThickness(2.0f);

    playerRotation = 0;
    objectRotation = 0.1;
    velocity = sf::Vector2f(0.0f, 0.0f);
    boosting = false;

    deltaClock.restart();
    deltaTime = 0.0f;
}

void Game::handleGameplayInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        state = GAME_PAUSED;
        return;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        playerRotation += rotationSpeed * deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        playerRotation -= rotationSpeed * deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        float thrustForce = thrust;
        if (boosting) {
            thrustForce *= boostMultiplier;
        }

        velocity.x += thrustForce * sinDeg(playerRotation) * deltaTime;
        velocity.y -= thrustForce * cosDeg(playerRotation) * deltaTime;

        if (!boosting) {
            boosting = true;
            boostClock.restart();
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        float thrustForce = thrust;
        if (boosting) {
            thrustForce *= boostMultiplier;
        }

        velocity.x -= thrustForce * sinDeg(playerRotation) * deltaTime;
        velocity.y += thrustForce * cosDeg(playerRotation) * deltaTime;

        if (!boosting) {
            boosting = true;
            boostClock.restart();
        }
    }
}

void Game::updateGame() {
    deltaTime = deltaClock.restart().asSeconds();

    if (boosting && boostClock.getElapsedTime().asSeconds() > 0.5) {
        boosting = false;
    }

    velocity *= damping;

    sf::Vector2f directionToStar = starPos - player.getPosition();
    float distance = std::sqrt(directionToStar.x * directionToStar.x + directionToStar.y * directionToStar.y);

    if (distance > minDistance) {
        float forceMagnitude = (gravitationStrength * starMass) / (distance * distance);
        forceMagnitude *= deltaTime;
        sf::Vector2f gravityForce = directionToStar / distance * forceMagnitude;

        float starAngularVelocity = 0.5f;
        sf::Vector2f tangentialVelocity(-directionToStar.y, directionToStar.x);
        tangentialVelocity /= distance;
        tangentialVelocity *= starAngularVelocity * std::sqrt(distance) * deltaTime;

        velocity += gravityForce + tangentialVelocity;
    }

    player.move(velocity);

    sf::Vector2f playerPos = player.getPosition();
    bool bounced = false;

    if (playerPos.x < borderPadding) {
        player.setPosition(borderPadding, playerPos.y);
        velocity.x = -velocity.x * bounceDamping;
        bounced = true;
    }
    else if (playerPos.x > screenWidth - borderPadding) {
        player.setPosition(screenWidth - borderPadding, playerPos.y);
        velocity.x = -velocity.x * bounceDamping;
        bounced = true;
    }

    if (playerPos.y < borderPadding) {
        player.setPosition(playerPos.x, borderPadding);
        velocity.y = -velocity.y * bounceDamping;
        bounced = true;
    }
    else if (playerPos.y > screenHeight - borderPadding) {
        player.setPosition(playerPos.x, screenHeight - borderPadding);
        velocity.y = -velocity.y * bounceDamping;
        bounced = true;
    }
    if (bounced) {
        playerRotation += (velocity.x > 0 ? 5 : -5) * deltaTime;
    }

    player.setRotation(playerRotation - 90);

    objectRotation += 30.0f * deltaTime;
    star.setRotation(-objectRotation);
}

void Game::renderGame() {
    window.clear(sf::Color(10, 10, 30));
    window.draw(borderRect);
    window.draw(star);
    window.draw(player);

    sf::Vertex velocityLine[] = {
        sf::Vertex(player.getPosition(), sf::Color::Green),
        sf::Vertex(player.getPosition() + velocity * 10.0f, sf::Color::Yellow)
    };
    window.draw(velocityLine, 2, sf::Lines);
}

float Game::sinDeg(float degrees) {
    return std::sin(degrees * 3.14159f / 180.0f);
}

float Game::cosDeg(float degrees) {
    return std::cos(degrees * 3.14159f / 180.0f);
}