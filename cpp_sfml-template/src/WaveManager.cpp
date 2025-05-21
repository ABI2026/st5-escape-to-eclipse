#include "WaveManager.h"

Wave::Wave(const std::vector<EnemySpawn>& spawns)
    : spawns(spawns) {
}

void Wave::update(float dt, std::vector<std::unique_ptr<Enemy>>& enemies, const sf::Texture& enemyTexture) {
    elapsed += dt;
    while (nextSpawnIndex < spawns.size() && spawns[nextSpawnIndex].timeOffset <= elapsed) {
        const auto& s = spawns[nextSpawnIndex];
        enemies.push_back(std::make_unique<Enemy>(s.position, enemyTexture));
        ++nextSpawnIndex;
    }
}


void WaveManager::addWave(const Wave& wave) {
    waves.push_back(wave);
}

bool Wave::isFinished() const {
    return nextSpawnIndex >= spawns.size();
}


void WaveManager::update(float dt, std::vector<std::unique_ptr<Enemy>>& enemies, const sf::Texture& enemyTexture) {
    if (currentWaveIndex < waves.size()) {
        waves[currentWaveIndex].update(dt, enemies, enemyTexture);
        if (waves[currentWaveIndex].isFinished()) {
            ++currentWaveIndex;
        }
    }
}


bool WaveManager::isFinished() const {
    return currentWaveIndex >= waves.size();
}
