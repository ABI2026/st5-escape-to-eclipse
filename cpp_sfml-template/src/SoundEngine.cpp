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
        music.setVolume(100);
        music.play();
    }
    std::cout << "PlayMusic Executed" << std::endl;
}

void SoundEngine::StopMusic()
{
    music.stop();
}

void SoundEngine::PlaySound()
{

}

void SoundEngine::StopSound()
{

}

void SoundEngine::SetVolume(float volume)
{
    std::cout << "Setting volume to: " << volume << std::endl;

    // Here you would typically set the volume in your audio engine
    // For example, if using FMOD:
    // sound->setVolume(volume);
}

float SoundEngine::GetVolume() const
{
    return 0.0f;
}