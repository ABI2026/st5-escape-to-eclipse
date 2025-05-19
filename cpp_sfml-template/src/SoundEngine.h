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
	void PlayToggleSound();
	void PlayUISelectSound();
	void PlaySelectSound();
	void PlayEnemyDeathSound();
	void SetVolume(float volume);
	float GetVolume() const;
	void ToggleMusic();

private:
	sf::Music music; //musik variable zum spielen von musik

	sf::SoundBuffer toggleSoundBuffer; //SoundBuffer zum laden von sound effekten
	sf::Sound toggleSound; //Sound variable zum spielen von sound effekten

	sf::SoundBuffer UISelectSoundBuffer;
	sf::Sound UISelectSound;

	sf::SoundBuffer selectSoundBuffer;
	sf::Sound selectSound;

	sf::SoundBuffer enemyDeathBuffer;
	sf::Sound enemyDeath;
};