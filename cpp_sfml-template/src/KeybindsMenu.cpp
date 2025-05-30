#include "KeybindsMenu.h"
#include "Button.h"

const int screenWidth = 1920;
const int screenHeight = 1080;

KeybindsMenu::KeybindsMenu(sf::RenderWindow& window)
    : Menu(window)
{
    float buttonWidth = 300.f;
    float buttonHeight = 80.f;
    float buttonX = screenWidth / 2.f - buttonWidth / 2.f;
    float buttonY = screenHeight * 0.8f;

    // Back button
    buttons.push_back(std::make_unique<Button>(
        buttonX, buttonY, buttonWidth, buttonHeight, font, "Back",
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200)
    ));
}

void KeybindsMenu::render() {
    Menu::render();

    // Title
    sf::Text titleText;
    titleText.setFont(font);
    titleText.setString("Keybinds");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(
        screenWidth / 2.f - titleText.getGlobalBounds().width / 2.f,
        screenHeight / 6.f
    );
    window.draw(titleText);

    std::vector<std::string> lines = {
        "Move Forward:   W / Up Arrow",
        "Move Backward:  S / Down Arrow",
        "Rotate Left:    A / Left Arrow",
        "Rotate Right:   D / Right Arrow",
        "Shoot:          F / M / Left Mouse",
        "Pause:          Escape",
        "Toggle Music:   N",
        "Endless Mode:   E (after all waves)"
    };

    float startY = screenHeight / 3.f;
    float lineSpacing = 60.f;
    float marginLeft = 337.5f;

    for (size_t i = 0; i < lines.size(); ++i) {
        sf::Text lineText;
        lineText.setFont(font);
        lineText.setCharacterSize(32);
        lineText.setFillColor(sf::Color::White);
        lineText.setString(lines[i]);
        lineText.setPosition(
            marginLeft,
            startY + i * lineSpacing
        );
        window.draw(lineText);
    }
}

int KeybindsMenu::handleInput() {
    if (buttons[0]->isClicked()) {
        return BACK;
    }
    return NONE;
}