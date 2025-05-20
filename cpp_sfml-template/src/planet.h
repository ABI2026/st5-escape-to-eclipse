#pragma once
#include <SFML/Graphics.hpp>

class Planet {
public:
    Planet(const sf::Vector2f& pos, float radius, float mass, const sf::Texture& texture);
    void render(sf::RenderWindow& window);
    sf::Vector2f getPosition() const;
    float getMass() const;
    void render(sf::RenderWindow& window) const; // const hinzufügen
private:
    sf::CircleShape shape;
    float mass;
};