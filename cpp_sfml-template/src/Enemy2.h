#ifndef ENEMY_H // IF NOT DEFINED 
#define ENEMY_H // DEFINE ENEMY_H

#include <SFML/Graphics.hpp>
#include"Bullet.h"

class Enemy 
{
public:
//An joseph seiner player class orientiert 
    Enemy(const sf::Vector2f& position, const sf::Texture& texture);

    void update(float deltaTime, const sf::Vector2f& playerPosition);
    void render(sf::RenderWindow& window) const;
    bool canShoot(float deltaTime);
    Bullet shoot(const sf::Texture& bulletTexture);
    float shootCooldown = 1.9f;
    float timeSinceLastShot = 0.1f;
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;

private:
    sf::RectangleShape enemyShape;
    sf::Vector2f velocity;
    float speed;
    float detectionRadius;

    void moveTowardsPlayer(const sf::Vector2f& playerPosition, float deltaTime);
};

#endif // END IF ENEMY_H
