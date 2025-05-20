#include "Obstacle.h"

Obstacle::Obstacle(const sf::Vector2f& pos, float radius) {
    shape.setRadius(radius);
    shape.setFillColor(sf::Color(150, 150, 150));
    shape.setOrigin(radius, radius);
    shape.setPosition(pos);
}

sf::FloatRect Obstacle::getBounds() const {
    return shape.getGlobalBounds();
}

void Obstacle::render(sf::RenderWindow& window) {
    window.draw(shape);
}

void Obstacle::render(sf::RenderWindow& window) const { // const hinzufügen
    window.draw(shape);
}