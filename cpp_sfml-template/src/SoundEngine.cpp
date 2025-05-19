#include "SoundEngine.h"
#include <iostream>
#include <string>

SoundEngine::SoundEngine()
{
}

SoundEngine::~SoundEngine()
{
    StopMusic();
}

void SoundEngine::PlayMusic()
{
    if (!music.openFromFile("Sound/solitude-dark-ambient-electronic-197737.ogg"))
    {
        std::cerr << "Error: Could not load music file." << std::endl;
        return;
    }
    else
    {
        std::cout << "Music file loaded successfully." << std::endl;
        music.setLoop(true); // Looped die Musik, aber nur den jeweiligen Track
        music.setVolume(100); // Lautstärke auf 100
        music.play(); // play music
    }
    std::cout << "PlayMusic Executed" << std::endl;
}

void SoundEngine::StopMusic()
{
    music.stop(); // stop music (selbsterklärend)
}

void SoundEngine::PlaySound()
{
	//Play einen sound (Placeholder (copy,paste) für die Struktur von den Soundeffekten)
}

void SoundEngine::StopSound()
{
    //Stop einen sound (Placeholder (copy,paste) für die Struktur von den Soundeffekten)
}

void SoundEngine::PlayToggleSound()
{
    if (!toggleSoundBuffer.loadFromFile("Sound/select-003-337609.ogg"))
    {
                std::cerr << "Error: Could not load sound file." << std::endl;
        return;
    }
    else
    {
		toggleSound.setBuffer(toggleSoundBuffer); // Setzt den Buffer für den Sound
        toggleSound.play();
    }
}

void SoundEngine::PlayUISelectSound()
{
    if (!UISelectSoundBuffer.loadFromFile("Sound/user-interface-click-234656.ogg"))
    {
        std::cerr << "Error: Could not load sound file." << std::endl;
        return;
    }
    else
    {
        UISelectSound.setBuffer(UISelectSoundBuffer); // Setzt den Buffer für den Sound
        UISelectSound.play();
	}
}

void SoundEngine::PlaySelectSound()
{
    if(!selectSoundBuffer.loadFromFile("Sound/video-games-select-337214.ogg"))
    {
        std::cerr << "Error: Could not load sound file." << std::endl;
        return;
    }
    else
    {
        selectSound.setBuffer(selectSoundBuffer); // Setzt den Buffer für den Sound
        selectSound.play();
	}
}

void SoundEngine::PlayEnemyDeathSound()
{
    if (!enemyDeathBuffer.loadFromFile("Sound/explosion-8-bit-8-314694.ogg"))
    {
        std::cerr << "Error: Could not load sound file." << std::endl;
        return;
    }
    else
    {
        enemyDeath.setBuffer(enemyDeathBuffer); // Setzt den Buffer für den Sound
        enemyDeath.play();
	}
}



void SoundEngine::SetVolume(float volume)
{
    std::cout << "Setting volume to: " << volume << std::endl;
	music.setVolume(volume); // Lautstärke setzen durch funktion
    // Here you would typically set the volume in your audio engine
    // For example, if using FMOD:
    // sound->setVolume(volume);
}

float SoundEngine::GetVolume() const
{
    return music.getVolume(); // DIGGA WAS SOLL DIE SCHEI?E KLEINES g -> SFML MUSIC, GROßES G -> SELFMADE CLASS; AUFPASSEN!!!!
}

void SoundEngine::ToggleMusic()
{
    PlayToggleSound();
    switch (music.getStatus())
    {
    case sf::Music::Playing:
        std::cout << "Music is playing. Pausing..." << std::endl;
        music.pause();
        break;
    case sf::Music::Paused:
    case sf::Music::Stopped:
        std::cout << "Music is paused/stopped. Resuming..." << std::endl;
        music.play();
        break;
    default:
        break;
    }
}
