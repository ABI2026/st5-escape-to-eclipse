#include "Obstacle.h"

Obstacle::Obstacle(const sf::Vector2f& pos, const sf::Vector2f& size) {
    shape.setSize(size);
    shape.setOrigin(size / 2.f);
    shape.setPosition(pos);
    shape.setFillColor(sf::Color(100, 100, 100)); // Grau
}

void Obstacle::render(sf::RenderWindow& window) const {
    window.draw(shape);
}

bool Obstacle::checkCollision(const sf::FloatRect& bounds) const {
    return shape.getGlobalBounds().intersects(bounds);
}
