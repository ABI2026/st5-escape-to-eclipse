#include "HighscoreManager.h"
#include <fstream>
#include <iostream>

HighscoreManager::HighscoreManager(const std::string& filename) : filename(filename) {
    loadHighscore();
}

void HighscoreManager::loadHighscore() {
    std::ifstream file(filename);
    if (file) file >> currentHighscore;
    else currentHighscore = 0;
}

void HighscoreManager::saveHighscore(int score) {
    if (score > currentHighscore) {
        std::ofstream file(filename);
        if (file) file << score;
        currentHighscore = score;
    }
}

int HighscoreManager::getHighscore() const {
    return currentHighscore;
}