#pragma once
#include <SFML/Audio.hpp>
class SoundEngine
{
public:
	SoundEngine();
	~SoundEngine();
	void Initialize();
	void Shutdown();
	void PlayMusic();
	void StopMusic();
	void PlaySound(const char* soundFile);
	void StopSound(const char* soundFile);
	void SetVolume(float volume);
	float GetVolume() const;
};

