#include "Bullet.h"
#include <cmath>
#include "GAme.h"

constexpr float BULLET_SPEED = 1000.0f;

Bullet::Bullet(const sf::Vector2f& pos, float rotationDeg, const sf::Texture& texture) {
    shape.setSize(sf::Vector2f(20.f, 25.f)); 
    shape.setOrigin(shape.getSize() / 2.0f);
    shape.setPosition(pos);
    shape.setRotation(rotationDeg);
    shape.setTexture(&texture);

    float angleRad = (rotationDeg) * 3.14159265f / 180.0f;
    velocity = sf::Vector2f(std::cos(angleRad), std::sin(angleRad)) * BULLET_SPEED;
}

void Bullet::update(float dt) {
    shape.move(velocity * dt);
}

void Bullet::render(sf::RenderWindow& window) {
    window.draw(shape);
}

bool Bullet::isOffscreen(int screenWidth, int screenHeight) const {
    sf::Vector2f pos = shape.getPosition();
    return (pos.x < 0 || pos.x > screenWidth || pos.y < 0 || pos.y > screenHeight);
}
