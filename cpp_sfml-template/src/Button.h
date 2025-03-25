#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;
    bool isPressed;

public:
    Button(float x, float y, float width, float height, sf::Font& font, std::string text,
        sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);

    bool isMouseOver(sf::RenderWindow& window);
    void update(sf::RenderWindow& window);
    bool isClicked();
    void render(sf::RenderWindow& window);
};

#endif // BUTTON_H