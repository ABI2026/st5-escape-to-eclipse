// Game.h

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "PauseMenu.h"
#include "SettingsMenu.h"
#include "Bullet.h"

class Game {
public:
    enum GameState { MAIN_MENU, GAME_PLAY, GAME_PAUSED, SETTINGS, EXIT };

    Game(sf::RenderWindow& window);
    void run();

private:
    void update();
    void render();
    void initGame();
    void handleMainMenuInput();
    void handlePauseMenuInput();
    void handleSettingsMenuInput();
    void handleGameplayInput();
    void updateGame();
    void renderGame();
    void updatePlayerTexture(bool moving, bool shooting);
    float sinDeg(float degrees);
    float cosDeg(float degrees);

    sf::RenderWindow& window;
    GameState state;
    sf::Clock shootCooldownClock;
    float shootCooldown = 0.15f;

    MainMenu mainMenu;
    PauseMenu pauseMenu;
    SettingsMenu settingsMenu;

    sf::Sprite player;
    sf::Texture playerTextures[4];

    sf::CircleShape star;
    sf::Texture starTexture;
    sf::Texture bulletTexture;
    std::vector<Bullet> bullets;

    sf::Vector2f velocity;
    sf::Vector2f starPos;

    sf::Clock deltaClock;
    sf::Clock boostClock;
    float deltaTime;
    float playerRotation;
    float objectRotation;

    bool boosting = false;
    bool isMoving = false;
    bool isShooting = false;

    const float borderPadding = 10.0f;
    const float bounceDamping = 0.7f;

    sf::RectangleShape borderRect;
};

#endif
