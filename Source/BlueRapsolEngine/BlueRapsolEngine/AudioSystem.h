#pragma once

#include <SFML/Audio.hpp>
#include <windows.h>

class AudioSystem {
private:
	sf::SoundBuffer buffer;
	sf::SoundBuffer buffer2;
	sf::SoundBuffer buffer3;
	sf::SoundBuffer buffer4;
	sf::Sound sound;
	sf::Sound sound2;
	sf::Sound sound3;
	sf::Sound sound4;

public:
	AudioSystem();
	void LoadBuffer();
	void SoundPlay(int x);
	void SoundStop(int y);

};
