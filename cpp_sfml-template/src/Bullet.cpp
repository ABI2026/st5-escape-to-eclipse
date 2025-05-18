#include "Bullet.h"
#include <cmath>

Bullet::Bullet(const sf::Vector2f& pos, float rotation, const sf::Texture& texture) {
    shape.setSize(sf::Vector2f(20, 8));
    shape.setOrigin(shape.getSize() / 2.f);
    shape.setTexture(&texture);
    shape.setPosition(pos);
    shape.setRotation(rotation);

    float speed = 600.0f;
    float angleRad = rotation * 3.14159265f / 180.0f;
    velocity.x = speed * std::cos(angleRad);
    velocity.y = speed * std::sin(angleRad);
}

void Bullet::update(float dt) {
    shape.move(velocity * dt);
}

void Bullet::render(sf::RenderWindow& window) {
    window.draw(shape);
}

bool Bullet::isOffscreen(int screenWidth, int screenHeight) const {

    sf::Vector2f pos = shape.getPosition();
    return pos.x < 0 || pos.x > screenWidth || pos.y < 0 || pos.y > screenHeight;
}
