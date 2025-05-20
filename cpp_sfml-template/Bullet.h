#pragma once
#pragma once
#include <SFML/Graphics.hpp>

class Bullet {
public:
    Bullet(const sf::Vector2f& pos, float rotation, const sf::Texture& texture);
    void update(float dt);
    void render(sf::RenderWindow& window);
    bool isOffscreen(int screenWidth, int screenHeight) const;

private:
    sf::RectangleShape shape;
    sf::Vector2f velocity;
};

