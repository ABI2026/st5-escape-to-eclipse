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
    if (!music.openFromFile("Sound/smoke-143172.ogg"))
    {
        std::cerr << "Error: Could not load music file." << std::endl;
        return;
    }
    else
    {
        std::cout << "Music file loaded successfully." << std::endl;
        music.setLoop(true); // Looped die Musik 
        music.setVolume(100); // Lautst�rke auf 100
        music.play(); // play music
    }
    std::cout << "PlayMusic Executed" << std::endl;
}

void SoundEngine::StopMusic()
{
    music.stop(); // stop music (selbsterkl�rend)
}

void SoundEngine::PlaySound()
{
	//Play einen sound (Placeholder (copy,paste) f�r die Struktur von den Soundeffekten)
}

void SoundEngine::StopSound()
{
    //Stop einen sound (Placeholder (copy,paste) f�r die Struktur von den Soundeffekten)
}

void SoundEngine::SetVolume(float volume)
{
    std::cout << "Setting volume to: " << volume << std::endl;
	music.setVolume(volume); // Lautst�rke setzen durch funktion
    // Here you would typically set the volume in your audio engine
    // For example, if using FMOD:
    // sound->setVolume(volume);
}

float SoundEngine::GetVolume() const
{
    return music.getVolume(); // DIGGA WAS SOLL DIE SCHEI?E KLEINES g -> SFML MUSIC, GRO�ES G -> SELFMADE CLASS; AUFPASSEN!!!!
}