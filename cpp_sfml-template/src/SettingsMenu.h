#ifndef SETTINGSMENU_H  
#define SETTINGSMENU_H  

#include "Menu.h"  
#include "SoundEngine.h" // Include SoundEngine header  

class SettingsMenu : public Menu {  
public:  
    enum SettingsMenuOptions { NONE, BACK };  

    // Update constructor to include SoundEngine reference  
    SettingsMenu(sf::RenderWindow& window, SoundEngine& soundEngine);  
    void render() override;  
    int handleInput() override;  

private:  
    SoundEngine& soundEngine; // Add SoundEngine reference as a member  
};  

#endif