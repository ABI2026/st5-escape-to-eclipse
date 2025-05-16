#ifndef ENEMY_H // IF NOT DEFINED 
#define ENEMY_H // DEFINE ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy 
{
public:
//An joseph seiner player class orientiert 
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

#endif // END IF ENEMY_H
