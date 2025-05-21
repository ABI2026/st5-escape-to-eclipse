#pragma once
#include <SFML/Graphics.hpp>

class Planet {
public:
    Planet(const sf::Vector2f& pos, float mass, float radius, const sf::Texture& texture);

    sf::Vector2f calculateGravity(const sf::Vector2f& objectPos) const;
    void render(sf::RenderWindow& window) const;

    const sf::Vector2f& getPosition() const;
    float getRadius() const;

private:
    sf::Vector2f position;
    float mass;
    float radius;
    sf::CircleShape shape;
};
