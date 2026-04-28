#include "SpriteRenderer.h"
#include "TransformComponent.h"
#include "Entity.h"
#include "AssetManager.h"
#include <iostream>
#include "BoxCollider.h"
#include "RotBoxCollider.h"

SpriteRenderer::SpriteRenderer()
{
	mSprite = sf::Sprite();
	mIsVisible = true;
	mOffest = { 0, 0 };
	
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::Resize(int width, int height)
{
	float factorWidth = width / (float)mSprite.getGlobalBounds().width;
	float factorHeight = height / (float)mSprite.getGlobalBounds().height;

	float factorMin = std::min(factorWidth, factorHeight);

	mSprite.scale(factorMin, factorMin);
}

void SpriteRenderer::Draw(sf::RenderWindow* _window)
{
	if (!mIsVisible) return;
	TransformComponent* transform = mOwner->GetComponent<TransformComponent>();

	Vector2f entityPos = transform->GetPos();
	Vector2f scale = transform->GetScale();

	mSprite.setScale(scale.x, scale.y);
	mSprite.setOrigin(mSprite.getLocalBounds().width * 0.5f, mSprite.getLocalBounds().height * 0.5f);
	mSprite.setRotation(transform->GetRotation());

	Vector2f tile = { mSprite.getScale().x, mSprite.getScale().y };

	Vector2f baseDrawPos = entityPos - tile * 0.5f;
	mSprite.setPosition(baseDrawPos + mOffest);
	_window->draw(mSprite);
	
}

void SpriteRenderer::Load(const std::string& filename)
{
	mSprite.setTexture(AssetManager::Get()->LoadTexture(filename));
}

void SpriteRenderer::SetFrame(int _frameWidth, int _frameHeight, int _frameX, int _frameY)
{
	mSprite.setTextureRect(sf::IntRect{ _frameX,_frameY,_frameWidth,_frameHeight });
}

void SpriteRenderer::SetOpacity(uint8_t _opacity)
{
	sf::Color c = mSprite.getColor();
	mSprite.setColor(sf::Color{ c.r,c.g,c.b,_opacity });
}

