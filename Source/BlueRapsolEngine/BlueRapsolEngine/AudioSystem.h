#pragma once

#include <SFML/Audio.hpp>
#include <windows.h>

class AudioSystem {
private:
	sf::SoundBuffer buffer;
	sf::Sound sound;

public:
	AudioSystem();
	void LoadBuffer();
	void SoundPlay();
	void SoundStop();
};