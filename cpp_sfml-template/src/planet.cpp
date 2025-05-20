#include "Planet.h"

Planet::Planet(const sf::Vector2f& pos, float radius, float mass, const sf::Texture& texture)
    : mass(mass) {
    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
    shape.setPosition(pos);
    shape.setTexture(&texture);
}

void Planet::render(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::Vector2f Planet::getPosition() const {
    return shape.getPosition();
}

float Planet::getMass() const {
    return mass;
}

void Planet::render(sf::RenderWindow& window) const { // const hinzufügen
    window.draw(shape);
}