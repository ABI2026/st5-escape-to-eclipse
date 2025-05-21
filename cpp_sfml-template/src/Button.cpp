#include "Button.h"

Button::Button(float x, float y, float width, float height, sf::Font& font, std::string text,
    sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor) {

    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setFillColor(idleColor);

    this->text.setFont(font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(30);

    this->text.setPosition(
        this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
        this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f - 6.1f
    );

    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;
    this->isPressed = false;
}

bool Button::isMouseOver(sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosView = window.mapPixelToCoords(mousePos);

    return shape.getGlobalBounds().contains(mousePosView);
}

void Button::update(sf::RenderWindow& window) {
    shape.setFillColor(idleColor);

    if (isMouseOver(window)) {
        shape.setFillColor(hoverColor);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            shape.setFillColor(activeColor);
            isPressed = true;
        }
        else {
            isPressed = false;
        }
    }
}

bool Button::isClicked() {
    bool clicked = isPressed;
    isPressed = false;
    return clicked;
}

void Button::render(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}