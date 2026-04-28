#include "Music.h"
#include <iostream>
void Music::Load(std::string fileName, bool isLoop) {
	
	if (!mMusic.openFromFile(fileName)) {
		std::cout << "Impossible de charger la music au chemin : " << fileName << std::endl;
		return;
	}
	mMusic.setLoop(isLoop);
}

void Music::Play() {
	mMusic.play();
}

void Music::Pause() {
	mMusic.pause();
}

void Music::Stop() {
	mMusic.stop();
}

void Music::SetVolume(int volume) {
	mMusic.setVolume(volume);
}
