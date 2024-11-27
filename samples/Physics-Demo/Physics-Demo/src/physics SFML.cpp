#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>

const int screenWidth = 1920;
const int screenHeight = 1080;

const float rotationSpeed = 0.4f;  // geschwindigkeit der rotation (grad pro frame)
const float thrust = 0.09f;        // beschleunigung
const float boostThrust = 0.03f;   // beschleunigung beim boosten (muss größer als gravitationsstärke sein um entkommen zu können)
const float damping = 0.99f;       // dämpfungsfaktor für die geschwindigkeit
const float gravitationStrength = 0.09f; // stärke der gravitationskraft
const float starMass = 1000.0f;    // masse des sterns (zur Kraftberechnung)
const float minDistance = 50.0f;  // mindestabstand um nicht direkt vom Stern abgesogen zu werden


float sinDeg(float degrees) {
    return std::sin(degrees * 3.14159f / 180.0f);
}

float cosDeg(float degrees) {
    return std::cos(degrees * 3.14159f / 180.0f);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "SFML Physics with Gravity", sf::Style::Fullscreen);

    // Player texture
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("C:/Users/User/source/repos/physics/template/Graphics/player.png")) {
        std::cerr << "Error: Could not load player texture!" << std::endl;
        return -1;
    }

    sf::Texture starTexture;
    if (!starTexture.loadFromFile("C:/Users/User/source/repos/physics/template/Graphics/star.png")) {
        std::cerr << "Error: Could not load player texture!" << std::endl;
        return -1;
    }

    // Player shape
    sf::RectangleShape player(sf::Vector2f(50, 50));
    player.setOrigin(25, 25);
    player.setPosition(screenWidth / 2 + 200, screenHeight / 2); 
    player.setTexture(&playerTexture);
    player.setRotation(-90);

    float playerRotation = 0;        
    float objectRotation = 0.1;
    sf::Vector2f velocity(0.0f, 0.0f);     
    bool boosting = false;               
    sf::Clock boostClock;                

    sf::Vector2f starPos(screenWidth / 2, screenHeight / 2);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            playerRotation += rotationSpeed;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            playerRotation -= rotationSpeed;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            velocity.x += (boosting ? boostThrust : thrust) * sinDeg(playerRotation);
            velocity.y -= (boosting ? boostThrust : thrust) * cosDeg(playerRotation);

            if (!boosting) {
                boosting = true;
                boostClock.restart();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            velocity.x -= (boosting ? boostThrust : thrust) * sinDeg(playerRotation);
            velocity.y += (boosting ? boostThrust : thrust) * cosDeg(playerRotation);

            if (!boosting) {
                boosting = true;
                boostClock.restart();
            }
        }

        if (boosting && boostClock.getElapsedTime().asSeconds() > 1) {
            boosting = false;
            velocity *= damping;  
        }

        sf::Vector2f directionToStar = starPos - player.getPosition(); 
        float distance = std::sqrt(directionToStar.x * directionToStar.x + directionToStar.y * directionToStar.y);

        if (distance > minDistance) {
            float forceMagnitude = (gravitationStrength * starMass) / (distance * distance);
            forceMagnitude *= 0.1f;
            sf::Vector2f gravityForce = directionToStar / distance * forceMagnitude;
            float starAngularVelocity = 0.005f;
            sf::Vector2f tangentialVelocity(-directionToStar.y, directionToStar.x);
            tangentialVelocity /= distance;
            tangentialVelocity *= starAngularVelocity * distance;
            tangentialVelocity *= 0.001f; 
            velocity += gravityForce + tangentialVelocity;
        }


        velocity *= damping;

        player.move(velocity);
        player.setRotation(playerRotation - 90);

        window.clear(sf::Color(30, 30, 30));
        window.draw(player);

        sf::CircleShape star(50);
        star.setFillColor(sf::Color::Yellow);
        star.setPosition(starPos.x - 10, starPos.y - 10);  
        star.setOrigin(50,50);
        star.setTexture(&starTexture);
        star.setRotation(-objectRotation);
        window.draw(star);
        objectRotation += 0.1;
        window.display();
    }

    return 0;
}
