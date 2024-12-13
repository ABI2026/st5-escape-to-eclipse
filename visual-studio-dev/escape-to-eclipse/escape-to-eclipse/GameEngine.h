#pragma once
#include <SFML/Graphics.hpp>

enum GameState {
	PAUSED,
	RUNNING
};

class GameEngine
{
	private:
		sf::RenderWindow* m_primary_window;
		GameState m_gameState;

		void init();
		void render() {};
		void origin();

	public:
		GameEngine();
		~GameEngine();

		void start();
};

