#include <SFML/Graphics.hpp>
#include "Game.h"
#include "SoundEngine.h"

const int screenWidth = 1920;
const int screenHeight = 1080;

int main() {

    sf::Listener::setGlobalVolume(75.f);// Globale Lautstärke auf 100, audio test
    SoundEngine soundEngine;

    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "ST5 Escape to Eclipse", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
    soundEngine.PlayMusic();
    Game game(window);
    game.run();
	
    

    return 0;
}