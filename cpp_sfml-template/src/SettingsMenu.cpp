#include "SettingsMenu.h"
#include "Button.h"

const int screenWidth = 1920;
const int screenHeight = 1080;

SettingsMenu::SettingsMenu(sf::RenderWindow& window, SoundEngine& soundEngine)
    : Menu(window), soundEngine(soundEngine) // Store reference to SoundEngine
{
    float buttonWidth = 300.f;
    float buttonHeight = 80.f;
    float buttonX = screenWidth / 2.f - buttonWidth / 2.f;
    float buttonY = screenHeight * 0.8f;
    float spacing = 120.f;

    // Back button
    buttons.push_back(std::make_unique<Button>(
        buttonX, buttonY, buttonWidth, buttonHeight, font, "Back",
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200)
    ));

    // Volume - button
    buttons.push_back(std::make_unique<Button>(
        buttonX - spacing, buttonY - 2 * spacing, buttonWidth / 2, buttonHeight, font, "- Vol",
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200)
    ));

    // Volume + button
    buttons.push_back(std::make_unique<Button>(
        buttonX + buttonWidth / 2 + spacing, buttonY - 2 * spacing, buttonWidth / 2, buttonHeight, font, "+ Vol",
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200)
    ));

    // Play button
    buttons.push_back(std::make_unique<Button>(
        buttonX, buttonY - 2 * spacing, buttonWidth / 2, buttonHeight, font, "Play",
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200)
    ));

    // Pause button
    buttons.push_back(std::make_unique<Button>(
        buttonX, buttonY - spacing, buttonWidth / 2, buttonHeight, font, "Pause",
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

    // Optionally, show current volume
    sf::Text volumeText;
    volumeText.setFont(font);
    volumeText.setString("Volume: " + std::to_string((int)soundEngine.GetVolume()));
    volumeText.setCharacterSize(30);
    volumeText.setFillColor(sf::Color::White);
    volumeText.setPosition(
        screenWidth / 2.f - volumeText.getGlobalBounds().width / 2.f,
        screenHeight / 2.f - volumeText.getGlobalBounds().height / 2.f
    );
    window.draw(volumeText);
}

int SettingsMenu::handleInput() {
    if (buttons[0]->isClicked()) {
        return BACK;
    }
    if (buttons[1]->isClicked()) {
        float vol = soundEngine.GetVolume();
        soundEngine.SetVolume(std::max(0.0f, vol - 5.0f));
    }
    if (buttons[2]->isClicked()) {
        float vol = soundEngine.GetVolume();
        soundEngine.SetVolume(std::min(100.0f, vol + 5.0f));
    }
    if (buttons[3]->isClicked()) {
        soundEngine.PlayMusic();
    }
    if (buttons[4]->isClicked()) {
        soundEngine.StopMusic();
    }
    return NONE;
}