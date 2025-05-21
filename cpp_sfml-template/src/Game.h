#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "PauseMenu.h"
#include "SettingsMenu.h"
#include "Bullet.h"
#include "Enemy2.h"
#include "SoundEngine.h"


class Game {
public:
    enum GameState { MAIN_MENU, SETTINGS, GAME_PLAY, GAME_PAUSED, EXIT };

    Game(sf::RenderWindow& window, SoundEngine& soundEngine);
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

    SoundEngine& soundEngine;

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
    sf::Texture enemybulletTexture;
    std::vector<Bullet> bullets;
    
    sf::Vector2f velocity;
    sf::Vector2f starPos;

    sf::Clock boostClock;
    sf::Clock deltaClock;
    float deltaTime;
    float playerRotation;
    float objectRotation;

    bool boosting = false;
    bool isMoving = false;
    bool isShooting = false;

    const float borderPadding = 10.0f;
    const float bounceDamping = 0.7f;

    sf::RectangleShape borderRect;

    std::vector<Enemy> enemies;
    sf::Texture enemyTexture;

    sf::Font font;
    sf::Text gameTimerText;
    sf::Clock gameTimerClock;

    int currentWave = 1;
    const int maxWaves = 7;
    sf::Clock waveSpawnClock;
    float waveInterval = 19.0f;
    bool endlessModeActive = false; // für den output unterm timer
//    
//   
//    bool boosting;
//   
//    
//  
//   
//
//    const float rotationSpeed = 180.0f;
//    const float thrust = 50.0;
//    const float boostMultiplier = 1.5f;
//    const float damping = 0.98f;
//    const float gravitationStrength = 500.0f;
//    const float starMass = 1000.0f;
//    const float minDistance = 20.0f;
//
//    const float borderPadding = 0.0f;
//    const float bounceDamping = 0.0f;
//
//    
//    
//   
//    
//
//public:
//    Game(sf::RenderWindow& window);
//    void run();
//    
//    
//    
};

#endif