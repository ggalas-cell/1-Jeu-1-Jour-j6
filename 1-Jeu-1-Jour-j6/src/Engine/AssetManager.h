#pragma once
#include <map>
#include <string>

namespace sf
{
	class Texture;
	class RenderWindow;
}

class AssetManager
{
private:
	const char* mPath = nullptr;
	static AssetManager* instance;

public:
	std::map<std::string, sf::Texture> mTextures;

	static AssetManager* Get();

	bool IsPathSet() { return mPath != nullptr; }
	void SetPath(const char* _p) { mPath = _p; }

	void LoadAssets();
	sf::Texture& LoadTexture(const std::string& filename, const char* filePath = NULL);
};

