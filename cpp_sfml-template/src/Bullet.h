#pragma once  
#include <SFML/Graphics.hpp>  

enum class BulletOwner { Player, Enemy };

class Bullet {  
public:  
    Bullet(const sf::Vector2f& pos, float rotation, const sf::Texture& texture, BulletOwner owner);  
    void update(float dt);  
    void render(sf::RenderWindow& window);  
    bool isOffscreen(int screenWidth, int screenHeight) const;  

    const sf::RectangleShape& getShape() const { return shape; }  
    BulletOwner getOwner() const { return owner; }

private:  
    sf::RectangleShape shape;  
    sf::Vector2f velocity;  
    BulletOwner owner;
};

