#include "SoundEngine.h"
#include <iostream>
#include <string>

SoundEngine::SoundEngine()
{
}

SoundEngine::~SoundEngine()
{
}

void SoundEngine::PlayMusic()
{
    sf::Music music;
    if (!music.openFromFile("smoke-143172.mp3"))
    {
        std::cerr << "Error: Could not load music file." << std::endl;
        return;
    }
    music.play();
}

void SoundEngine::StopMusic()
{
}

void SoundEngine::PlaySound(const char* soundFile)
{

}

void SoundEngine::StopSound(const char* soundFile)
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