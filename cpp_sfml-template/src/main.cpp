#include <SFML/Graphics.hpp>
#include "Game.h"
#include "SoundEngine.h"
#include <iostream>

const int screenWidth = 1920;
const int screenHeight = 1080;

int main() {


	sf::Image icon; // Icon für das Fenster 
    if (!icon.loadFromFile("Graphics/icon.png")) // NUR SFML, das andere ist bei der resource (für Windows)
    { 
        std::cerr << "Failed to load icon image.\n";
        return -1;
    }
    

    sf::Listener::setGlobalVolume(75.f);// Globale Lautstärke auf 100, audio test
	SoundEngine soundEngine; // SoundEngine initialisieren

    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "ST5 Escape to Eclipse", sf::Style::Fullscreen);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	window.setFramerateLimit(60); // FPS auf 60 setzen
	soundEngine.PlayMusic(); // Musik starten
    Game game(window);
    game.run();
	
    
	std::cerr << soundEngine.GetVolume() << " %"; // debug für lautstärke (nur wenn das spiel geschlossen wird)
    return 0;
}