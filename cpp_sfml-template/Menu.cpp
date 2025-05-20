#include "Menu.h"
#include "Button.h"
#include <iostream>

const int screenWidth = 1920;
const int screenHeight = 1080;

Menu::Menu(sf::RenderWindow& window) : window(window) {
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cerr << "Error: Could not load font!" << std::endl;
    }

    background.setSize(sf::Vector2f(screenWidth, screenHeight));
    background.setFillColor(sf::Color(0, 0, 0, 200));
}

void Menu::update() {
    for (auto& button : buttons) {
        button->update(window);
    }
}

void Menu::render() {
    window.draw(background);
    for (auto& button : buttons) {
        button->render(window);
    }
}