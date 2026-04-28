#include "Animation.h"
#include "Entity.h"
#include "SpriteRenderer.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>

using json = nlohmann::json;

Animation::Animation() {
	mDuration = 0.05f;
	//mNmbFrame = 4;
	mCurrentIndexX = 0;
	mCurrentIndexY = 0;
}

void Animation::Update()
{
	float deltaTime = mOwner->GetDeltaTime();
	mDuration -= deltaTime;
	Anim anim = mAnims[mCurrentAnim];
	if (mDuration <= 0) {
		mDuration += anim.frameTime;
		mCurrentIndexY *= mFrameHeight;
		if (!anim.loop&& mCurrentIndexX >= anim.frameNmb - 1) {
			return;
		}
		mCurrentIndexX = (mCurrentIndexX + 1) % anim.frameNmb;
		mOwner->GetComponent<SpriteRenderer>()->SetFrame(mFrameWidth, mFrameHeight, mFrameWidth * mCurrentIndexX, mCurrentIndexY);
	}
}

void Animation::SetIndexY(int newIndex) { 
	mCurrentIndexY = newIndex; 
}

void Animation::SetCurrentAnim(std::string currentAnim){
	mCurrentAnim = currentAnim;
	mCurrentIndexX = 0;
}

bool Animation::IsFinish() {
	return mCurrentIndexX >= mAnims[mCurrentAnim].frameNmb - 1;
}


void Animation::LoadAnimInfos(const char* path) {
	std::ifstream f(path);
	json data = json::parse(f);
	if (data.contains("frame_size")) {
		mFrameHeight = data["frame_size"]["height"];
		mFrameWidth = data["frame_size"]["width"];
	}
	if (data.contains("animation")) {
		for (auto& [name, value] : data["animation"].items()) {
			Anim anim = { value["frame"], value["loop"], value["frameTime"] };
			mAnims.insert({ name, anim }); 
		}
	}
}
