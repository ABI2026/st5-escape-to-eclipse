#pragma once

#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <list>
#include <unordered_map>

namespace sf {
	class Color;
}

namespace GameConfigManagement
{
	struct RGBA {
		std::uint8_t m_r;
		std::uint8_t m_g;
		std::uint8_t m_b;
		std::uint8_t m_a;

		RGBA() = default;
		RGBA(std::uint8_t p_r, std::uint8_t p_g, std::uint8_t p_b, std::uint8_t p_a) : m_r(p_r), m_g(p_g), m_b(p_b), m_a(p_a) {};
	};

	class UITheme {
		public:
			UITheme(std::string p_theme_name = "");

			void writeThemeToFile();
			void loadThemeFromFile(std::string fileName);
			void loadThemeFromMemory(UITheme p_theme);
			
			//Defining Accessors
			void setHeadlineFontname(std::string p_fontName);
			std::string getHeadlineFontName();
			void setDescriptionFontName(std::string p_fontName);
			std::string getDescriptionFontName();
			void setPrimaryAccentColor(RGBA p_primaryAccentColor);
			RGBA getPrimaryAccentColor();
			void setSecondaryAccentColor(RGBA p_secondaryAccentColor);
			RGBA getSecondaryAccentColor();
			void setFontColor(RGBA p_fontColor);
			RGBA getFontColor();
			void setThemeName(std::string p_themeName);
			std::string getThemeName();

		private:
			std::string m_themeName;
			std::string m_headlineFontName;
			std::string m_descriptionFontName;
			RGBA m_primaryAccentColor;
			RGBA m_secondaryAccentColor;
			RGBA m_fontColor;
	};


	class Configuration {
		public:
			Configuration();
			bool loadConfigurationFromFile(std::string path);
			void writeConfigurationToFile(std::string path);
		private:
			std::unordered_map<std::string, std::string> m_variables;
			std::string splitString(std::string& string, std::string delimiter);
			std::string* trim(std::string* untrimmed_string);
	};
}

