#pragma once  
#include <SFML/Audio.hpp>  
class SoundEngine
{
public:
	SoundEngine();
	~SoundEngine();
	void Initialize();
	void PlayMusic();
	void StopMusic();
	void PlaySound();
	void StopSound();
	void SetVolume(float volume);
	float GetVolume() const;

private:
	sf::Music music; //musik variable zum spielen von musik
};