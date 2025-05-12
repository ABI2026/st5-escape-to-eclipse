#include "Enemy.h"
#include <cmath>

Enemy::Enemy(const sf::Vector2f& position, const sf::Texture& texture)
    : speed(100.0f), detectionRadius(300.0f) {
    enemyShape.setRadius(25.0f);
    enemyShape.setOrigin(25.0f, 25.0f);
    enemyShape.setPosition(position);
    enemyShape.setTexture(&texture);
}

void Enemy::update(float deltaTime, const sf::Vector2f& playerPosition) {
    float distanceToPlayer = std::sqrt(
        std::pow(playerPosition.x - enemyShape.getPosition().x, 2) +
        std::pow(playerPosition.y - enemyShape.getPosition().y, 2)
    );

    if (distanceToPlayer <= detectionRadius) {
        moveTowardsPlayer(playerPosition, deltaTime);
    }
}

void Enemy::render(sf::RenderWindow& window) const {
    window.draw(enemyShape);
}

sf::Vector2f Enemy::getPosition() const {
    return enemyShape.getPosition();
}

float Enemy::getRadius() const {
    return enemyShape.getRadius();
}

void Enemy::moveTowardsPlayer(const sf::Vector2f& playerPosition, float deltaTime) {
    sf::Vector2f direction = playerPosition - enemyShape.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length != 0) {
        direction /= length; // Normalisieren
    }

    velocity = direction * speed * deltaTime;
    enemyShape.move(velocity);
}
