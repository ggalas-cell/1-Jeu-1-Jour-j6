#include "AudioManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>

#include <filesystem>
namespace fs = std::filesystem;

SoundManager* SoundManager::instance = nullptr;

SoundManager* SoundManager::Get()
{
	if (instance == nullptr) {
		instance = new SoundManager();
	}
	return instance;
}


void SoundManager::LoadSounds()
{
	if (!IsPathSet()) SetPath("../../assets/Audios/Sons");
	
	
	for (const auto& entry : fs::directory_iterator(mPath)) {
		std::string filename = entry.path().stem().string();
		LoadSound(filename, entry.path().string().c_str());
	}

}

sf::SoundBuffer& SoundManager::LoadSound(const std::string& filename, const char* filePath)
{
	if (mBuffer.find(filename) != mBuffer.end())
		return mBuffer[filename];

	sf::SoundBuffer buffer;

	if (!buffer.loadFromFile(filePath))
		std::cout << "Error in loading Soundbuffer : \"" << filePath << "\"" << std::endl;
	mBuffer[filename] = buffer;

	return mBuffer[filename];
}
