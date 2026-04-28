#include "Sound.h"
#include "AudioManager.h"

void Sound::Load(std::string fileName) {
	mBuffer = SoundManager::Get()->LoadSound(fileName);
}

void Sound::Play() {
	mSound.setBuffer(mBuffer);
	mSound.play();
}

void Sound::SetVolume(int volume) {
	mSound.setVolume(volume);
}