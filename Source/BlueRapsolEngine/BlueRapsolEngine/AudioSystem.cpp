#include "AudioSystem.h"


AudioSystem::AudioSystem() {

}


void AudioSystem::LoadBuffer() {
	if (!buffer.loadFromFile("../../../Assets/MMBGM.wav")) {
		OutputDebugString(L"\n[Error] Cannot load bgm sound.");
	}
	sound.setBuffer(buffer);
	sound.setVolume(20);

	if (!buffer2.loadFromFile("../../../Assets/Cannon.wav")) {
		OutputDebugString(L"\n[Error] Cannot load cannon sound.");
	}
	sound2.setBuffer(buffer2);
	sound2.setVolume(20);

	if (!buffer3.loadFromFile("../../../Assets/Explosion.wav")) {
		OutputDebugString(L"\n[Error] Cannot load explosion sound.");
	}
	sound3.setBuffer(buffer3);
	sound3.setVolume(20);

	if (!buffer4.loadFromFile("../../../Assets/test4.wav")) {
		OutputDebugString(L"\n[Error] Cannot load test sound.");
	}
	sound4.setBuffer(buffer4);

}

void AudioSystem::SoundPlay(int x) {
	if (x == 1) {
		sound.play();
		sound.setLoop(true);
	}
	else if (x == 2) {
		sound2.play();
	}
	else if (x == 3) {
		sound3.play();
	}
	else if (x == 4) {
		sound4.play();
	}
}

void AudioSystem::SoundStop(int y) {
	sound.stop();
	if (y == 1) {
		sound.play();
	}
	else if (y == 2) {
		sound2.play();
	}
	else if (y == 3) {
		sound3.play();
	}
	else if (y == 4) {
		sound4.play();
	}
}