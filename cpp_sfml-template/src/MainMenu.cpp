#include "MainMenu.h"
#include "Button.h"
#include <iostream>
const int screenWidth = 1920;
const int screenHeight = 1080;
MainMenu::MainMenu(sf::RenderWindow& window) : Menu(window) {
    sf::Text titleText;
    titleText.setFont(font);
    titleText.setString("ST5 Escape To Eclipse");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(
        screenWidth / 2.f - titleText.getGlobalBounds().width / 2.f,
        screenHeight / 4.f - titleText.getGlobalBounds().height / 2.f
    );

    float buttonWidth = 300.f;
    float buttonHeight = 80.f;
    float buttonX = screenWidth / 2.f - buttonWidth / 2.f;
    float buttonY = screenHeight / 2.f - buttonHeight / 2.f;
    float buttonSpacing = 120.f;

    buttons.push_back(std::make_unique<Button>(
        buttonX, buttonY, buttonWidth, buttonHeight, font, "Start",
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200)
    ));

    buttons.push_back(std::make_unique<Button>(
        buttonX, buttonY + buttonSpacing, buttonWidth, buttonHeight, font, "Settings",
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200)
    ));

    buttons.push_back(std::make_unique<Button>(
        buttonX, buttonY + 2 * buttonSpacing, buttonWidth, buttonHeight, font, "Exit",
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200)
    ));
}

void MainMenu::render() {
    Menu::render();
    sf::Text titleText;
    titleText.setFont(font);
    titleText.setString("ST5 Escape To Eclipse");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(
        screenWidth / 2.f - titleText.getGlobalBounds().width / 2.f,
        screenHeight / 4.f - titleText.getGlobalBounds().height / 2.f
    );
    window.draw(titleText);

    // Highscore text
    sf::Text highscoreText;
    highscoreText.setFont(font);
    highscoreText.setCharacterSize(36);
    highscoreText.setFillColor(sf::Color(255, 215, 0)); // Gold color
    highscoreText.setString("Highscore: " + std::to_string(currentHighscore));
    highscoreText.setPosition(
        screenWidth / 2.f - highscoreText.getLocalBounds().width / 2.f,
        titleText.getPosition().y + titleText.getGlobalBounds().height + 20.f
    );
    window.draw(highscoreText);

}

int MainMenu::handleInput() {
    if (buttons[0]->isClicked()) {
        return START;
    }
    else if (buttons[1]->isClicked()) {
        return SETTINGS;
    }
    else if (buttons[2]->isClicked()) {
        return EXIT;
    }
    return NONE;
}

void MainMenu::setHighscore(int highscore)
{
    currentHighscore = highscore;
}