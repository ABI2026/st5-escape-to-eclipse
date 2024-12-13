#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameEngine.h"

int main() {

	GameEngine* engine = new GameEngine();

	engine->start();

	return 0;
}