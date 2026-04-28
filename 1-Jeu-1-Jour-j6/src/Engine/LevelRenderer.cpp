#include "LevelRenderer.h"
#include "AssetManager.h"
#include "TransformComponent.h"
#include "Entity.h"
#include <iostream>

LevelRenderer::LevelRenderer(const std::vector<int>& _tiles, int _width, int _height, int _tileSize, const std::string& _tilesetName)
{
	mTiles = _tiles;
	mWidth = _width;
	mHeight = _height;
	mTileSize = _tileSize;

	mTexture = &AssetManager::Get()->LoadTexture(_tilesetName);

	mTilesetColumns = mTexture->getSize().x / mTileSize;

	mVertices.setPrimitiveType(sf::Quads);
	mVertices.resize(mWidth * mHeight * 4);
}

LevelRenderer::~LevelRenderer()
{
}

void LevelRenderer::BuildVertices(const Vector2f& origin, const Vector2f& scale)
{
    float scaledW = mTileSize * scale.x;
    float scaledH = mTileSize * scale.y;

    for (int y = 0; y < mHeight; y++)
    {
        for (int x = 0; x < mWidth; x++)
        {
            int index = y * mWidth + x;
            int id = mTiles[index];

            sf::Vertex* quad = &mVertices[index * 4];

            if (id == 0) {
                // tile vide : quad transparent (alpha 0)
                for (int i = 0; i < 4; i++) quad[i].color = sf::Color::Transparent;
                continue;
            }

            id -= 1;
            int frameX = (id % mTilesetColumns) * mTileSize;
            int frameY = (id / mTilesetColumns) * mTileSize;

            float px = origin.x + x * scaledW;
            float py = origin.y + y * scaledH;

            // positions monde
            quad[0].position = sf::Vector2f(px, py);
            quad[1].position = sf::Vector2f(px + scaledW, py);
            quad[2].position = sf::Vector2f(px + scaledW, py + scaledH);
            quad[3].position = sf::Vector2f(px, py + scaledH);

            // coordonnées texture
            quad[0].texCoords = sf::Vector2f(frameX, frameY);
            quad[1].texCoords = sf::Vector2f(frameX + mTileSize, frameY);
            quad[2].texCoords = sf::Vector2f(frameX + mTileSize, frameY + mTileSize);
            quad[3].texCoords = sf::Vector2f(frameX, frameY + mTileSize);

            for (int i = 0; i < 4; i++) quad[i].color = sf::Color::White;
        }
    }
    mDirty = false;
}

void LevelRenderer::Draw(sf::RenderWindow* window)
{
    TransformComponent* transform = mOwner->GetComponent<TransformComponent>();
    Vector2f origin = transform->GetPos();
    Vector2f scale = transform->GetScale();

    if (mDirty)
        BuildVertices(origin, scale);

    sf::RenderStates states;
    states.texture = mTexture;
    window->draw(mVertices, states);
}