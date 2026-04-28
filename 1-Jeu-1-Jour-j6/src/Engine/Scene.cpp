#include "Scene.h"
#include "CollisionSystem.h"
#include "TagComponent.h"
#include "TransformComponent.h"
#include "GameManager.h"
#include "Entity.h"

int Scene::GetWindowWidth() const
{
	return mpGameManager->mWindowWidth;
}

int Scene::GetWindowHeight() const
{
	return mpGameManager->mWindowHeight;
}

float Scene::GetDeltaTime() const
{
	return mpGameManager->mDeltaTime;
}

Scene::~Scene()
{
}

Entity* Scene::CreateEntity()
{
	Entity* ent = new Entity;
	mEntitiesToAdd.push_back(ent);
	ent->AddComponent<TransformComponent>();
	
	return ent;
}

void Scene::DestroyEntity(Entity* _ent)
{
	_ent->Destroy();
}

void Scene::DestroyAllEntitiesWithTag(const std::string& _tag)
{
	for (Entity* ent : FindAllEntitiesWithTag(_tag))
		DestroyEntity(ent);
}

void Scene::DestroyAllEntities()
{
	for (Entity* ent : mEntities)
		DestroyEntity(ent);
}

Entity* Scene::FindByTag(const std::string& _tag)
{
	for (Entity* ent : mEntities)
	{
		if (TagComponent* tag = ent->GetComponent<TagComponent>())
		{
			if (tag->Is(_tag))
				return ent;
		}
	}

	return nullptr;
}

std::list<Entity*> Scene::FindAllEntitiesWithTag(const std::string& _tag)
{
	std::list<Entity*> result;

	for (Entity* ent : mEntities)
	{
		if (TagComponent* tag = ent->GetComponent<TagComponent>())
		{
			if (tag->Is(_tag))
				result.push_back(ent);
		}
	}

	return result;
}



void Scene::Draw(sf::RenderWindow* _window)
{
	for (Entity* ent : mEntities)
	{
		ent->Draw(_window);
	}
	OnDraw(_window);
}

void Scene::Update()
{
	for (auto it = mEntities.begin(); it != mEntities.end();)
	{
		Entity* ent = *it;

		ent->Update();

		if (ent->ToDestroy() == false)
		{
			++it;
			continue;
		}

		mEntitiesToDestroy.push_back(ent);
		it = mEntities.erase(it);
	}

	mEntitiesToDestroy.clear();

	for (auto it = mEntitiesToAdd.begin(); it != mEntitiesToAdd.end(); ++it)
	{
		mEntities.push_back(*it);
	}

	mEntitiesToAdd.clear();

	OnUpdate();
}

void Scene::FixedUpdate()
{
	for (Entity* ent : mEntities)
		ent->FixedUpdate();
}

void Scene::DestroyEntitiesNow() {
	DestroyAllEntities();
	for (auto it = mEntities.begin(); it != mEntities.end();)
	{
		Entity* ent = *it;

		if (ent->ToDestroy() == false)
		{
			++it;
			continue;
		}

		mEntitiesToDestroy.push_back(ent);
		it = mEntities.erase(it);
	}

	mEntitiesToDestroy.clear();
}