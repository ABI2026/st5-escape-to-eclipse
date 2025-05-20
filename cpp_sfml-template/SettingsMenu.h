#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include "Menu.h"

class SettingsMenu : public Menu {
public:
    enum SettingsMenuOptions { NONE, BACK };

    SettingsMenu(sf::RenderWindow& window);
    void render() override;
    int handleInput() override;
};

#endif