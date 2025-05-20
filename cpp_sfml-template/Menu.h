#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Button.h"

class Menu {
protected:
    sf::RenderWindow& window;
    sf::Font font;
    std::vector<std::unique_ptr<Button>> buttons;
    sf::RectangleShape background;

public:
    Menu(sf::RenderWindow& window);
    virtual void update();
    virtual void render();
    virtual int handleInput() = 0;
};

#endif