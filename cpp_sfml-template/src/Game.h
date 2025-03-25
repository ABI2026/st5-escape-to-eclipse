#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "PauseMenu.h"
#include "SettingsMenu.h"

class Game {
public:
    enum GameState { MAIN_MENU, SETTINGS, GAME_PLAY, GAME_PAUSED, EXIT };

private:
    sf::RenderWindow& window;
    GameState state;

    MainMenu mainMenu;
    PauseMenu pauseMenu;
    SettingsMenu settingsMenu;

    sf::Texture playerTexture;
    sf::Texture starTexture;
    sf::RectangleShape player;
    sf::CircleShape star;

    sf::RectangleShape borderRect;

    float playerRotation;
    float objectRotation;
    sf::Vector2f velocity;
    bool boosting;
    sf::Clock boostClock;
    sf::Vector2f starPos;
    sf::Clock deltaClock;
    float deltaTime;

    const float rotationSpeed = 180.0f;
    const float thrust = 50.0;
    const float boostMultiplier = 1.5f;
    const float damping = 0.98f;
    const float gravitationStrength = 500.0f;
    const float starMass = 1000.0f;
    const float minDistance = 20.0f;

    const float borderPadding = 0.0f;
    const float bounceDamping = 0.0f;

    float sinDeg(float degrees);
    float cosDeg(float degrees);
    void initGame();
    void handleGameplayInput();
    void updateGame();
    void renderGame();

public:
    Game(sf::RenderWindow& window);
    void run();
    void update();
    void render();
    void handleMainMenuInput();
    void handlePauseMenuInput();
    void handleSettingsMenuInput();
};

#endif