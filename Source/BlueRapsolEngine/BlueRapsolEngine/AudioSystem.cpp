#include "AudioSystem.h"

AudioSystem::AudioSystem() {
	LoadBuffer();
}

void AudioSystem::LoadBuffer() {
	if (!buffer.loadFromFile("../../../Assets/zzz.wav")) {
		OutputDebugString(L"\n[Error] Cannot load test sound.");
	}

	sound.setBuffer(buffer);
}

void AudioSystem::SoundPlay() {
	sound.play();
}

void AudioSystem::SoundStop() {
	sound.stop();
}
