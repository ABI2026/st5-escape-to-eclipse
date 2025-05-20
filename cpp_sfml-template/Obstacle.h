#pragma once
#include <SFML/Graphics.hpp>

class Obstacle {
public:
    Obstacle(const sf::Vector2f& pos, float radius);
    sf::FloatRect getBounds() const;
    void render(sf::RenderWindow& window);
    void render(sf::RenderWindow& window) const; // const hinzufügen
private:
    sf::CircleShape shape;
};