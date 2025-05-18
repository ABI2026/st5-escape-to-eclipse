#include "Game.h"
#include"Bullet.h"
#include <iostream>
#include <cmath>

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
    std::vector<std::string> textureFiles = {
        "Graphics/PlayerStand.png",
        "Graphics/PlayerFlight.png",
        "Graphics/PlayerShotStand.png",
        "Graphics/PlayerShotFlight.png"
    };

    for (size_t i = 0; i < textureFiles.size(); ++i) {
        if (!playerTextures[i].loadFromFile(textureFiles[i])) {
            std::cerr << "Error: Could not load " << textureFiles[i] << std::endl;
            state = EXIT;
            return;
        }
        player.setTexture(playerTextures[0]);
        sf::Vector2u texSize = playerTextures[0].getSize();
        player.setOrigin(texSize.x / 2.0f, texSize.y / 2.0f);
    }

    if (!font.loadFromFile("Font/QuinqueFive.ttf")) {
        std::cerr << "Error: Could not load font!" << std::endl;
        state = EXIT;
        return;
    }

    if (!starTexture.loadFromFile("Graphics/star.png")) {
        std::cerr << "Error: Could not load star texture!" << std::endl;
        state = EXIT;
        return;
    }

   

    if (!bulletTexture.loadFromFile("Graphics/PlayerShot.png")) {
        std::cerr << "Error: Could not load bullet texture!" << std::endl;
        state = EXIT;
        return;
    }
    if (!enemyTexture.loadFromFile("Graphics/enemy.png")) {
        std::cerr << "Error: Could not load enemy texture!" << std::endl;
        state = EXIT;
        return;
    }

    enemies.clear();
    enemies.emplace_back(sf::Vector2f(400, 400), enemyTexture); // TESTS!!!!!
    enemies.emplace_back(sf::Vector2f(800, 200), enemyTexture);
    enemies.emplace_back(sf::Vector2f(1200, 700), enemyTexture);

    player.setPosition(screenWidth / 2 + 200, screenHeight / 2);
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

    gameTimerText.setFont(font); 
	gameTimerText.setCharacterSize(28); // größe Text
    gameTimerText.setFillColor(sf::Color::White); //weiß ggrrrrrr
    gameTimerText.setPosition(20.f, 20.f); //oben links

    playerRotation = 0;
    objectRotation = 0.1f;
    velocity = sf::Vector2f(0.0f, 0.0f);
    boosting = false;
    isShooting = false;
    isMoving = false;

    deltaClock.restart();
    deltaTime = 0.0f;
}

void Game::handleGameplayInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        state = GAME_PAUSED;
        return;
    }

    isMoving = false;
    isShooting = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        playerRotation += rotationSpeed * deltaTime;
        isMoving = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        playerRotation -= rotationSpeed * deltaTime;
        isMoving = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        float thrustForce = thrust;
        if (boosting) thrustForce *= boostMultiplier;

        velocity.x += thrustForce * sinDeg(playerRotation) * deltaTime;
        velocity.y -= thrustForce * cosDeg(playerRotation) * deltaTime;

        if (!boosting) {
            boosting = true;
            boostClock.restart();
        }
        isMoving = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        float thrustForce = thrust;
        if (boosting) thrustForce *= boostMultiplier;

        velocity.x -= thrustForce * sinDeg(playerRotation) * deltaTime;
        velocity.y += thrustForce * cosDeg(playerRotation) * deltaTime;

        if (!boosting) {
            boosting = true;
            boostClock.restart();
        }
        isMoving = false;
    }
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::F) || sf::Keyboard::isKeyPressed(sf::Keyboard::M))) {
        if (shootCooldownClock.getElapsedTime().asSeconds() >= shootCooldown) {
            isShooting = true;

            float bulletRotation = player.getRotation();
            sf::Vector2f bulletPosition = player.getPosition();

            bullets.emplace_back(bulletPosition, bulletRotation, bulletTexture);

            shootCooldownClock.restart(); // Cooldown zurücksetzen
        }
    }
    else {
        isShooting = false;
    }


    updatePlayerTexture(isMoving, isShooting);
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

    for (auto& enemy : enemies) {
        enemy.update(deltaTime, player.getPosition());
    }

    sf::Time elapsed = gameTimerClock.getElapsedTime();
    int minutes = static_cast<int>(elapsed.asSeconds()) / 60;
    int seconds = static_cast<int>(elapsed.asSeconds()) % 60;

    char buffer[16];
    std::snprintf(buffer, sizeof(buffer), "%02d:%02d", minutes, seconds);
    gameTimerText.setString(buffer);


    objectRotation += 30.0f * deltaTime;
    star.setRotation(-objectRotation);
}

void Game::renderGame() {
    window.clear(sf::Color(10, 10, 30));
    window.draw(borderRect);
    window.draw(star);
    window.draw(player);
    window.draw(gameTimerText);

    for (const auto& enemy : enemies) {
        enemy.render(window);
    }
    for (auto& bullet : bullets) {
        bullet.render(window);
    }

    sf::Vertex velocityLine[] = {
        sf::Vertex(player.getPosition(), sf::Color::Green),
        sf::Vertex(player.getPosition() + velocity * 10.0f, sf::Color::Yellow)
    };
    window.draw(velocityLine, 2, sf::Lines);
}

void Game::updatePlayerTexture(bool moving, bool shooting) {
    int index = 0;
    if (moving && shooting) index = 3;
    else if (shooting) index = 2;
    else if (moving) index = 1;

    player.setTexture(playerTextures[index]);
    sf::Vector2u texSize = playerTextures[index].getSize();
    player.setOrigin(texSize.x / 2.0f, texSize.y / 2.0f);
}


float Game::sinDeg(float degrees) {
    return std::sin(degrees * 3.14159f / 180.0f);
}

float Game::cosDeg(float degrees) {
    return std::cos(degrees * 3.14159f / 180.0f);
}