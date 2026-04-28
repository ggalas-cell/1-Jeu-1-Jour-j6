#include "AssetManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>

#include <filesystem>
namespace fs = std::filesystem;

AssetManager* AssetManager::instance = nullptr;

AssetManager* AssetManager::Get()
{
	if (instance == nullptr) {
		instance = new AssetManager();
	}
	return instance;
}


void AssetManager::LoadAssets()
{
	if (!IsPathSet()) SetPath("../../assets/Images/");
	std::cout << "Chemin assets : " << mPath << std::endl;
	std::cout << "Chemin courant : " << fs::current_path() << std::endl;

	if (!fs::exists(mPath)) {
		std::cout << "ERREUR : dossier introuvable !" << std::endl;
		return;
	}

	for (const auto& entry : fs::recursive_directory_iterator(mPath)) {
		if (!entry.is_regular_file()) continue;
		std::string ext = entry.path().extension().string();
		if (ext == ".png" || ext == ".jpg" || ext == ".jpeg")
		{
			std::string filename = entry.path().stem().string();
			LoadTexture(filename, entry.path().string().c_str());
		}
	}
}

sf::Texture& AssetManager::LoadTexture(const std::string& filename, const char* filePath)
{
	if (mTextures.find(filename) != mTextures.end()) 
		return mTextures[filename];

	sf::Texture texture;

	if (!texture.loadFromFile(filePath))
		std::cout << "assetManager : Error in loading texture : \"" << filePath << "\"" << std::endl;

	mTextures[filename] = texture;

	return mTextures[filename];
}

