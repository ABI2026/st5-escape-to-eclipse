#pragma once
#include <string>

class HighscoreManager {
public:
    HighscoreManager(const std::string& filename);
    int getHighscore() const;
    void saveHighscore(int score);

private:
    std::string filename;
    int currentHighscore = 0;
    void loadHighscore();
};