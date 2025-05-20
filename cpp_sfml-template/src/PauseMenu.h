#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "Menu.h"

class PauseMenu : public Menu {
public:
    enum PauseMenuOptions { NONE, RESUME, SETTINGS, MAIN_MENU, EXIT };

    PauseMenu(sf::RenderWindow& window);
    void render() override;
    int handleInput() override;
};

#endif