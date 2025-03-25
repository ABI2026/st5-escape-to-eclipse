#include <SFML/Graphics.hpp>
#include "Game.h"

const int screenWidth = 1920;
const int screenHeight = 1080;

int main() {
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "ST5 Escape to Eclipse", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    Game game(window);
    game.run();

    return 0;
}