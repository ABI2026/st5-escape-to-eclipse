#pragma once
#include <SFML/Graphics.hpp>

class Obstacle {
public:
    Obstacle(const sf::Vector2f& pos, const sf::Vector2f& size);

    void render(sf::RenderWindow& window) const;
    bool checkCollision(const sf::FloatRect& bounds) const;
    sf::FloatRect getBounds() const {
        return shape.getGlobalBounds();
    }

private:
    sf::RectangleShape shape;
};
