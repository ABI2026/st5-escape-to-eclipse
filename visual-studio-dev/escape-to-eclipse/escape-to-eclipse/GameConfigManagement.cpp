#include "GameConfigManagement.h"

// UI-Theme definitions

GameConfigManagement::UITheme::UITheme(std::string p_theme_name) {
	this->m_themeName = p_theme_name;
}

// Configuration class definitions

GameConfigManagement::Configuration::Configuration() {
	//
}

bool GameConfigManagement::Configuration::loadConfigurationFromFile(std::string path) {
	std::fstream file;

	file.open(path);

	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			std::cout << line;
		}
		return true;
	}
	return false;
}

//std::string GameConfigManagement::Configuration::splitString(std::string& string, std::string delimiter) {
//	
//}