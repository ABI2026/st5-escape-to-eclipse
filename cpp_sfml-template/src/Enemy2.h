#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy(const sf::Vector2f& position, const sf::Texture& texture);

    void update(float deltaTime, const sf::Vector2f& playerPosition);
    void render(sf::RenderWindow& window) const;

    sf::Vector2f getPosition() const;
    float getRadius() const;

private:
    sf::CircleShape enemyShape;
    sf::Vector2f velocity;
    float speed;
    float detectionRadius;

    void moveTowardsPlayer(const sf::Vector2f& playerPosition, float deltaTime);
};

#endif // ENEMY_H
