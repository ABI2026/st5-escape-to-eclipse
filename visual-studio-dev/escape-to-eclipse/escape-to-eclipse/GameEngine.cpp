#include "GameEngine.h"

GameEngine::GameEngine() {
	//empty constructor
}

GameEngine::~GameEngine() {
	delete this->m_primary_window;
}

void GameEngine::init() {
	this->m_gameState = GameState::RUNNING;
	this->m_primary_window = new sf::RenderWindow(sf::VideoMode(1500, 900), "Escape To Eclipse");
	origin();
}

void GameEngine::origin() {
	sf::Event ev;
	while (this->m_primary_window->isOpen()) {
		if (!this->m_gameState == GameState::RUNNING) {
			//switch to pause layer
		}
		while (this->m_primary_window->pollEvent(ev)) {
			//will be replaced by event system
		}
		this->m_primary_window->display();
		this->m_primary_window->clear(sf::Color::Black);
	}
}

void GameEngine::start() {
	init();
}