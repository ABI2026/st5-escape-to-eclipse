#ifndef MAINMENU_H
#define MAINMENU_H

#include "Menu.h"

class MainMenu : public Menu {
public:
    enum MainMenuOptions { NONE, START, SETTINGS, EXIT };

    MainMenu(sf::RenderWindow& window);
    void render() override;
    int handleInput() override;
    void setHighscore(int highscore);
private: 
	int currentHighscore;
};

#endif