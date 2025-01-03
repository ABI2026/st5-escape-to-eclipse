#pragma once

#include <unordered_map>

namespace sf {
	class RenderWindow;
}

class EventHandler
{
	public:
		EventHandler(sf::RenderWindow* window);
		~EventHandler();
		void process_events();
		void update();
	private:
		
};

