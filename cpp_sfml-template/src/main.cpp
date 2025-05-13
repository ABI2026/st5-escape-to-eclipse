#include <SFML/Graphics.hpp>
#include "Game.h"
#include "SoundEngine.h"
#include <iostream>

const int screenWidth = 1920;
const int screenHeight = 1080;

int main() {


    sf::Image icon;
    if (!icon.loadFromFile("Graphics/icon.png")) {
        std::cerr << "Failed to load icon image.\n";
        return -1;
    }
    

    sf::Listener::setGlobalVolume(75.f);// Globale Lautstärke auf 100, audio test
    SoundEngine soundEngine;

    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "ST5 Escape to Eclipse", sf::Style::Fullscreen);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    window.setFramerateLimit(60);
    soundEngine.PlayMusic();
    Game game(window);
    game.run();
	
    
	std::cerr << soundEngine.GetVolume() << " %" ;
    return 0;
}