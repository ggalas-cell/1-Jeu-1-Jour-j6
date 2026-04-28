#include "LevelLoader.h"
#include "SceneManager.h"
#include "Entity.h"
#include "Scene.h"
#include "TransformComponent.h"
#include "LevelRenderer.h"
#include "TagComponent.h"

#include <sstream>
#include <tinyxml2.h>
#include <iostream>

using namespace tinyxml2;

void LevelLoader::Load(const std::string& path, const std::string& tilesetName, Vector2f scale)
{
	XMLDocument level;
	if (level.LoadFile(path.c_str()) != XML_SUCCESS)
		return;

	XMLElement* map = level.FirstChildElement("map");

	int width = map->IntAttribute("width");
	int height = map->IntAttribute("height");
	int tileSize = map->IntAttribute("tilewidth");

	XMLElement* layer = map->FirstChildElement("layer");
	XMLElement* data = layer->FirstChildElement("data");

	std::vector<int> tiles;
	std::stringstream ss(data->GetText());
	std::string value;

	while (std::getline(ss, value, ','))
		tiles.push_back(std::stoi(value));

	Scene* scene = SceneManager::Get()->GetCurrentScene();

	Entity* levelEntity = scene->CreateEntity();
	
	TransformComponent* transform = levelEntity->GetComponent<TransformComponent>();
	transform->SetPos({ 0,0 });
	transform->SetScale(scale);

	levelEntity->AddComponent<LevelRenderer>(tiles, width, height, tileSize, tilesetName);
	levelEntity->AddComponent<TagComponent>("LevelMap");

	for (XMLElement* group = map->FirstChildElement("objectgroup"); group; group = group->NextSiblingElement("objectgroup"))
	{
		const char* layerName = group->Attribute("name");

		if (!layerName) continue;


		for (XMLElement* obj = group->FirstChildElement("object"); obj; obj = obj->NextSiblingElement("object"))
		{
			float x = obj->FloatAttribute("x") * scale.x;
			float y = obj->FloatAttribute("y") * scale.y;
			float w = obj->FloatAttribute("width") * scale.x;
			float h = obj->FloatAttribute("height") * scale.y;
			float rot = obj->FloatAttribute("rotation");

			scene->Create(std::string(layerName), x, y, w, h, rot);
		}
	}
}
