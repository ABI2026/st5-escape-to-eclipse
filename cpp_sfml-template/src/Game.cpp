#include "Game.h"
#include"Bullet.h"
#include <iostream>
#include <cmath>
#include "Planet.h"
#include "Obstacle.h"
#include "WaveManager.h"

const int screenWidth = 1920; 
const int screenHeight = 1080;

const float rotationSpeed = 180.0f;
const float thrust = 50.0f;
const float boostMultiplier = 1.5f;
const float damping = 0.98f;
const float gravitationStrength = 1000.0f;
const float starMass = 1500.0f;
const float minDistance = 20.0f;
const float bounceDamping = 0.8f;
const float borderPadding = 50.0f;

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
        window.clear();
        renderGame();
        break;
    case GAME_PAUSED:
        window.clear();
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
        "Graphics/PlayerStand.png", "Graphics/PlayerFlight.png",
        "Graphics/PlayerShotStand.png", "Graphics/PlayerShotFlight.png"
    };

    for (size_t i = 0; i < textureFiles.size(); ++i) {
        if (!playerTextures[i].loadFromFile(textureFiles[i])) {
            std::cerr << "Error: Could not load " << textureFiles[i] << std::endl;
            state = EXIT; return;
        }
    }

    player.setTexture(playerTextures[0]);
    player.setOrigin(playerTextures[0].getSize().x / 2.0f, playerTextures[0].getSize().y / 2.0f);

    font.loadFromFile("Font/QuinqueFive.ttf");
    starTexture.loadFromFile("Graphics/star.png");
    bulletTexture.loadFromFile("Graphics/PlayerShot.png");
    enemybulletTexture.loadFromFile("Graphics/EnemyShoot.png");
    if (!enemyTexture.loadFromFile("Graphics/EnemyFlight.png")) {
        std::cerr << "Error: Could not load enemy texture" << std::endl;
        state = EXIT; return;
    }


    player.setPosition(screenWidth / 2 + 200, screenHeight / 2);
    player.setRotation(-90);

    star.setRadius(50);
    star.setOrigin(50, 50);
    star.setPosition(screenWidth / 2, screenHeight / 2);
    star.setTexture(&starTexture);
    starPos = star.getPosition();

    borderRect.setSize(sf::Vector2f(screenWidth - 20, screenHeight - 20));
    borderRect.setPosition(10, 10);
    borderRect.setFillColor(sf::Color::Transparent);
    borderRect.setOutlineColor(sf::Color(100, 100, 255, 100));
    borderRect.setOutlineThickness(2.0f);

    gameTimerText.setFont(font);
    gameTimerText.setCharacterSize(28);
    gameTimerText.setFillColor(sf::Color::White);
    gameTimerText.setPosition(20.f, 20.f);

    planets = {
        { sf::Vector2f(960, 540), 3000.0f, 70.0f, starTexture },
        { sf::Vector2f(300, 300), 2000.0f, 60.0f, starTexture },
        { sf::Vector2f(1600, 800), 2500.0f, 65.0f, starTexture }
    };
    obstacles = {
        { sf::Vector2f(500, 500), sf::Vector2f(100, 100) },
        { sf::Vector2f(1000, 300), sf::Vector2f(80, 120) },
        { sf::Vector2f(1400, 700), sf::Vector2f(150, 50) }
    };

    waveManager = WaveManager();
    waveManager.addWave(Wave({
        { 0.f, sf::Vector2f(400, 400), 0 },
        { 2.f, sf::Vector2f(800, 200), 0 },
        { 4.f, sf::Vector2f(1200, 700), 0 },
        }));

    enemies.clear();
    currentWave = 1;
    waveSpawnClock.restart();

    playerRotation = 0;
    objectRotation = 0.1f;
    velocity = sf::Vector2f(0.f, 0.f);
    boosting = isMoving = isShooting = false;
    deltaClock.restart();
    deltaTime = 0.f;
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

    if (boosting && boostClock.getElapsedTime().asSeconds() > 0.5f) {
        boosting = false;
    }

    sf::Vector2f totalGravity(0.f, 0.f);
    for (const auto& planet : planets) {
        totalGravity += planet.calculateGravity(player.getPosition()) * deltaTime;
    }
    velocity += totalGravity;

    if (currentWave <= maxWaves && waveSpawnClock.getElapsedTime().asSeconds() >= waveInterval) {
        for (int i = 0; i < currentWave; ++i) {
            sf::Vector2f spawnPos(
                100 + std::rand() % (screenWidth - 200),
                100 + std::rand() % (screenHeight - 200)
            );
            enemies.push_back(std::make_unique<Enemy>(spawnPos, enemyTexture));
        }
        ++currentWave;
        waveSpawnClock.restart();
    }



    for (const auto& obstacle : obstacles) {
        if (obstacle.checkCollision(player.getGlobalBounds())) {
            // Berechne Überschneidung (Überlappungsbereich)
            sf::FloatRect playerBounds = player.getGlobalBounds();
            sf::FloatRect obstacleBounds = obstacle.getBounds();

            // Wie tief ist die Überschneidung in x und y?
            float overlapLeft = (playerBounds.left + playerBounds.width) - obstacleBounds.left;
            float overlapRight = (obstacleBounds.left + obstacleBounds.width) - playerBounds.left;
            float overlapTop = (playerBounds.top + playerBounds.height) - obstacleBounds.top;
            float overlapBottom = (obstacleBounds.top + obstacleBounds.height) - playerBounds.top;

            // Kleinste Überschneidung in x und y finden (für Push-out Richtung)
            float minOverlapX = (overlapLeft < overlapRight) ? overlapLeft : -overlapRight;
            float minOverlapY = (overlapTop < overlapBottom) ? overlapTop : -overlapBottom;

            // Korrigiere die Position entlang der Richtung mit dem kleineren Überlappungswert
            if (std::abs(minOverlapX) < std::abs(minOverlapY)) {
                // Korrigiere horizontal
                player.move(-minOverlapX, 0);
                velocity.x = -velocity.x * bounceDamping;  // Bounce horizontal
            }
            else {
                // Korrigiere vertikal
                player.move(0, -minOverlapY);
                velocity.y = -velocity.y * bounceDamping;  // Bounce vertikal
            }
        }
    }


    // Update Wellenlogik
    waveManager.update(deltaTime, enemies, enemyTexture);



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
        enemy->update(deltaTime, player.getPosition());
    }
    for (auto& bullet : bullets) 
    {
        bullet.update(deltaTime);
    }
    
    for (auto& enemy : enemies) {
        enemy->update(deltaTime, playerPos);
        if (enemy->canShoot(deltaTime)) {
            bullets.push_back(enemy->shoot(enemybulletTexture));
            bullets.push_back(Bullet(enemy->getPosition(), enemy->getRotation(), enemybulletTexture, BulletOwner::Enemy));
            soundEngine.PlayShootSound(); // shoot sound for enemy
        }
    }

    for (auto& bullet : bullets) {
        bullet.update(deltaTime);
    }


    //bullet-enemy collisions
    for (auto& enemy : enemies)
    {
        for (auto& bullet : bullets)
        {
            if (bullet.getOwner() == BulletOwner::Player)
            {
                if (enemy->getPosition().x < bullet.getShape().getPosition().x + enemy->getSize().x / 2 &&
                    enemy->getPosition().x + enemy->getSize().x / 2 > bullet.getShape().getPosition().x &&
                    enemy->getPosition().y < bullet.getShape().getPosition().y + enemy->getSize().y / 2 &&
                    enemy->getPosition().y + enemy->getSize().y / 2 > bullet.getShape().getPosition().y)
                {
                    enemy->takeDamage();
                    bullet = bullets.back();
                    bullets.pop_back();
                    break;
                }
            }
        }
    }

    // Remove dead enemies
  //  enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
  //      [](const Enemy& e) { return e.isDead(); }), enemies.end());

	// REMOVE DEAD ENEMIES AND PLAY SOUND, YAY
    for (auto it = enemies.begin(); it != enemies.end(); ) {
        if ((*it)->isDead()) {
            soundEngine.PlayEnemyDeathSound();
            it = enemies.erase(it);
        }
        else {
            ++it;
        }
    }

}

void Game::renderGame() {
    window.draw(borderRect);
    window.draw(star);
    window.draw(player);
    window.draw(gameTimerText);

    for (auto& planet : planets)
        planet.render(window);

    for (auto& obstacle : obstacles)
        obstacle.render(window);

    for (auto& bullet : bullets)
        bullet.render(window);

    for (auto& enemy : enemies)
        enemy->render(window);


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
    return std::sin(degrees * 3.14159265f / 180.0f);
}

float Game::cosDeg(float degrees) {
    return std::cos(degrees * 3.14159265f / 180.0f);
}
