#include "Planet.h"
#include <cmath>

Planet::Planet(const sf::Vector2f& pos, float mass, float radius, const sf::Texture& texture)
    : position(pos), mass(mass), radius(radius) {
    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
    shape.setPosition(pos);
    shape.setTexture(&texture);
}

sf::Vector2f Planet::calculateGravity(const sf::Vector2f& objectPos) const {
    sf::Vector2f direction = position - objectPos;
    float distance = std::max(30.0f, std::sqrt(direction.x * direction.x + direction.y * direction.y));
    float force = mass / (distance * distance);
    return (direction / distance) * force;
}

void Planet::render(sf::RenderWindow& window) const {
    window.draw(shape);
}

const sf::Vector2f& Planet::getPosition() const {
    return position;
}

float Planet::getRadius() const {
    return radius;
}
