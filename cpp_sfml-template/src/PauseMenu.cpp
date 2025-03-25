#include "PauseMenu.h"
#include "Button.h"
#include <iostream>

const int screenWidth = 1920;
const int screenHeight = 1080;

PauseMenu::PauseMenu(sf::RenderWindow& window) : Menu(window) {
    float buttonWidth = 300.f;
    float buttonHeight = 80.f;
    float buttonX = screenWidth / 2.f - buttonWidth / 2.f;
    float buttonY = screenHeight / 2.f - 2 * buttonHeight;
    float buttonSpacing = 120.f;

    buttons.push_back(std::make_unique<Button>(
        buttonX, buttonY, buttonWidth, buttonHeight, font, "Resume",
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200)
    ));

    buttons.push_back(std::make_unique<Button>(
        buttonX, buttonY + buttonSpacing, buttonWidth, buttonHeight, font, "Settings",
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200)
    ));

    buttons.push_back(std::make_unique<Button>(
        buttonX, buttonY + 2 * buttonSpacing, buttonWidth, buttonHeight, font, "Main Menu",
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200)
    ));

    buttons.push_back(std::make_unique<Button>(
        buttonX, buttonY + 3 * buttonSpacing, buttonWidth, buttonHeight, font, "Exit",
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200)
    ));
}

void PauseMenu::render() {
    Menu::render();
    sf::Text titleText;
    titleText.setFont(font);
    titleText.setString("Paused");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(
        screenWidth / 2.f - titleText.getGlobalBounds().width / 2.f,
        screenHeight / 4.f - titleText.getGlobalBounds().height / 2.f
    );
    window.draw(titleText);
}

int PauseMenu::handleInput() {
    if (buttons[0]->isClicked()) {
        return RESUME;
    }
    else if (buttons[1]->isClicked()) {
        return SETTINGS;
    }
    else if (buttons[2]->isClicked()) {
        return MAIN_MENU;
    }
    else if (buttons[3]->isClicked()) {
        return EXIT;
    }
    return NONE;
}