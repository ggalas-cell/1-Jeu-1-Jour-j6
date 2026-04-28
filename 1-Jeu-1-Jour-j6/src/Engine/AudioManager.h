#pragma once

#include "SFML/Audio.hpp"
#include <iostream>
#include <map>

class SoundManager {
private:
	const char* mPath = nullptr;
	static SoundManager* instance;

public:
	std::map<std::string, sf::SoundBuffer> mBuffer;

	static SoundManager* Get();
	bool IsPathSet() { return mPath != nullptr; }
	void SetPath(const char* _p) { mPath = _p; }

	void LoadSounds();

	sf::SoundBuffer& LoadSound(const std::string& filename, const char* filePath = NULL);
};