#pragma once
#include "Component.h"
#include "Updatable.h"
#include "SFML/Graphics.hpp"
#include <vector>
class SpriteRenderer;

struct Anim {
	int frameNmb;
	bool loop;
	float frameTime;
};
class Animation : public Component, public Updatable
{

	

	int mFrameWidth;
	int mFrameHeight;
	int mCurrentIndexX;
	int mCurrentIndexY;
	float mDuration;
	float mCurrentTime;
	std::map<std::string, Anim> mAnims;
	std::string mCurrentAnim;

public:
	Animation();
	void Update() override;
	void SetSprite(SpriteRenderer* sprite);
	void LoadAnimInfos(const char* path);
	bool IsFinish();
	int GetFrameHeight() { return mFrameHeight; }
	int SetFrameHeight(int newHeight) { mFrameHeight = newHeight; }
	void SetIndexY(int newIndex);
	std::string GetCurrentAnimName() { return mCurrentAnim; }
	void SetCurrentAnim(std::string currentAnim);
};