#include "SettingsMenu.h"
#include "Button.h"

const int screenWidth = 1920;
const int screenHeight = 1080;

SettingsMenu::SettingsMenu(sf::RenderWindow& window) : Menu(window) {
    float buttonWidth = 300.f;
    float buttonHeight = 80.f;
    float buttonX = screenWidth / 2.f - buttonWidth / 2.f;
    float buttonY = screenHeight * 0.8f;

    buttons.push_back(std::make_unique<Button>(
        buttonX, buttonY, buttonWidth, buttonHeight, font, "Back",
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200)
    ));
}

void SettingsMenu::render() {
    Menu::render();

    sf::Text titleText;
    titleText.setFont(font);
    titleText.setString("Settings");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(
        screenWidth / 2.f - titleText.getGlobalBounds().width / 2.f,
        screenHeight / 4.f - titleText.getGlobalBounds().height / 2.f
    );
    window.draw(titleText);

    sf::Text placeholderText;
    placeholderText.setFont(font);
    placeholderText.setString("Platzhalter");
    placeholderText.setCharacterSize(30);
    placeholderText.setFillColor(sf::Color::White);
    placeholderText.setPosition(
        screenWidth / 2.f - placeholderText.getGlobalBounds().width / 2.f,
        screenHeight / 2.f - placeholderText.getGlobalBounds().height / 2.f
    );
    window.draw(placeholderText);
}

int SettingsMenu::handleInput(){
    if (buttons[0]->isClicked()) {
        return BACK;
    }
    return NONE;
}