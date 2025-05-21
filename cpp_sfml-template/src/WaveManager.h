#pragma once
#include <SFML/System.hpp>
#include <vector>
#include <memory>
#include "Enemy2.h"

struct EnemySpawn {
    float timeOffset;
    sf::Vector2f position;
    int type;
};

class Wave {
public:
    Wave(const std::vector<EnemySpawn>& spawns);

    void update(float dt, std::vector<std::unique_ptr<Enemy>>& enemies, const sf::Texture& enemyTexture);
    bool isFinished() const;
private:
    std::vector<EnemySpawn> spawns;
    float elapsed = 0.f;
    size_t nextSpawnIndex = 0;
};

class WaveManager {
public:
    WaveManager() = default;  // expliziter Default-Konstruktor

    void addWave(const Wave& wave);
    void update(float dt, std::vector<std::unique_ptr<Enemy>>& enemies, const sf::Texture& enemyTexture);
    bool isFinished() const;

private:
    std::vector<Wave> waves;
    size_t currentWaveIndex = 0;
};
