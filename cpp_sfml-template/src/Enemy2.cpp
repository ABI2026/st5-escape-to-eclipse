#include "Enemy2.h"
#include <cmath>

Enemy::Enemy(const sf::Vector2f& position, const sf::Texture& texture)
    : speed(100.0f), detectionRadius(300.0f) 
{
    enemyShape.setSize(sf::Vector2f(75.f, 75.f)); // z.?B. 50x50 Pixel
    enemyShape.setOrigin(25.0f, 25.0f);
    enemyShape.setPosition(position);
    enemyShape.setTexture(&texture);
}

void Enemy::update(float deltaTime, const sf::Vector2f& playerPosition)
{
    float distanceToPlayer = std::sqrt(
        std::pow(playerPosition.x - enemyShape.getPosition().x, 2) +
        std::pow(playerPosition.y - enemyShape.getPosition().y, 2)
    );

   // if (distanceToPlayer <= detectionRadius)
    //{                 
        moveTowardsPlayer(playerPosition, deltaTime); // DIGGA WENN ICH MEINEN EIGENEN SCHEI� LESEN K�NNTE, STUNDEN DIE ICH DAS GESUCHT HABE: 2
    //}

    // Calculate angle to player and set rotation
    sf::Vector2f toPlayer = playerPosition - enemyShape.getPosition();
    float angleRad = std::atan2(toPlayer.y, toPlayer.x);
    float angleDeg = angleRad * 180.0f / 3.14159265f;
    enemyShape.setRotation(angleDeg); // ROTATION ZUM SPIELER
}

void Enemy::render(sf::RenderWindow& window) const
{
    window.draw(enemyShape);
}

sf::Vector2f Enemy::getPosition() const
{
    return enemyShape.getPosition();
}

sf::Vector2f Enemy::getSize() const 
{
    return enemyShape.getSize();
}
bool Enemy::canShoot(float deltaTime)
{
    timeSinceLastShot += deltaTime;
    if (timeSinceLastShot >= shootCooldown)
    {
        timeSinceLastShot = 0.0f;
        return true;
    }
    return false;
}

Bullet Enemy::shoot(const sf::Texture& bulletTexture)
{
    return Bullet(enemyShape.getPosition(), enemyShape.getRotation(), bulletTexture, BulletOwner::Enemy);
}


void Enemy::moveTowardsPlayer(const sf::Vector2f& playerPosition, float deltaTime)
{
    sf::Vector2f direction = playerPosition - enemyShape.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length != 0)
    {
        direction /= length; // Normalisieren
    }

    velocity = direction * speed * deltaTime;
    enemyShape.move(velocity);
}


void Enemy::takeDamage()
{
    health--;
}

bool Enemy::isDead() const
{
    return health <= 0;
}
float Enemy::getRotation() const
{
    return enemyShape.getRotation();
}