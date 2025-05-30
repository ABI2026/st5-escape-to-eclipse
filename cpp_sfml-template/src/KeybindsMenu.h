#ifndef KEYBINDSMENU_H
#define KEYBINDSMENU_H

#include "Menu.h"

class KeybindsMenu : public Menu {
public:
    enum KeybindsMenuOptions { NONE, BACK };

    KeybindsMenu(sf::RenderWindow& window);
    void render() override;
    int handleInput() override;
};

#endif