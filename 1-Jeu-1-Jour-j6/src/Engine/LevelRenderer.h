#pragma once
#include "Component.h"
#include "Drawable.h"
#include "Vector2f.h"
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class LevelRenderer : public Component, public Drawable
{
private:
	std::vector<int> mTiles;
	sf::Sprite mSprite;
	sf::VertexArray mVertices;
	sf::Texture* mTexture;
	int mWidth;
	int mHeight;
	int mTileSize;
	int mTilesetColumns;

	void BuildVertices(const Vector2f& origin, const Vector2f& scale);
	bool mDirty = true;

public:
	LevelRenderer(const std::vector<int>& _tiles, int _width, int _height, int _tileSize, const std::string& _tilesetName);
	~LevelRenderer();

	Vector2f GetLevelSize() const { return Vector2f{ (float)mWidth * mTileSize, (float)mHeight * mTileSize }; }

	void Draw(sf::RenderWindow* window) override;
};

