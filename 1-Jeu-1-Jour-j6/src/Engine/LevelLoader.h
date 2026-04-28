#pragma once
#include <string>
#include "Vector2f.h"

class Scene;

class LevelLoader
{
public:
	static void Load(const std::string& path, const std::string& tilesetName, Vector2f scale = { 1.f,1.f });
};

