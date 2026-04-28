#pragma once
#include "Component.h"
#include "Drawable.h"
#include "Vector2f.h"

namespace sf {
	class Sprite;
	class RenderWindow;
}

class SpriteRenderer : public Component, public Drawable
{

	sf::Sprite mSprite;
	bool mIsVisible;

	Vector2f mOffest;

	Vector2f m_tiledSize;

public:
	SpriteRenderer();
	~SpriteRenderer();
	void Resize(int width, int height);
	void Draw(sf::RenderWindow* _window) override;
	void Load(const std::string& _filePath);
	void SetFrame(int _frameWidth, int _frameHeight, int _frameX, int _frameY);
	void SetOffset(float _offsetX, float _offsetY) { mOffest = { _offsetX, _offsetY }; }
	void SetOpacity(uint8_t _opacity);
};

