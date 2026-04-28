#include "SceneManager.h"
#include "Scene.h"
#include "GameManager.h"
#include "CollisionSystem.h"

SceneManager* SceneManager::instance = nullptr;

SceneManager* SceneManager::Get()
{
	if (instance == nullptr) {
		instance = new SceneManager();
	}
	return instance;
}

SceneManager::SceneManager()
{
	mChangeScene = true;
}

SceneManager::~SceneManager()
{
	for (auto& pair : mScenes)
		delete pair.second;
}

Scene* SceneManager::GetCurrentScene()
{
	return mScenes[mCurrentScene];
}

std::string SceneManager::GetCurrentSceneID()
{
	return mCurrentScene;
}

void SceneManager::ChangeScene(const std::string& _id)
{
	mNextScene = _id;
	mChangeScene = true;
}

void SceneManager::ReloadScene()
{
	mChangeScene = true;
}

void SceneManager::Update()
{
	if (mChangeScene)
	{
		mScenes[mCurrentScene]->OnExit();

		mScenes[mCurrentScene]->DestroyEntitiesNow();

		CollisionSystem::Get()->ClearAll();

		mCurrentScene = mNextScene;

		mScenes[mCurrentScene]->OnEnter();

		mChangeScene = false;
	}
	mScenes[mCurrentScene]->Update();
}

void SceneManager::FixedUpdate()
{
	mScenes[mCurrentScene]->FixedUpdate();
}

void SceneManager::Draw(sf::RenderWindow* _window)
{
	mScenes[mCurrentScene]->Draw(_window);
}

void SceneManager::AddScene(const std::string& _id, Scene* _scene)
{
	_scene->SetGameManager(GameManager::Get());
	mScenes[_id] = _scene;
}

Scene* SceneManager::FindSceneById(const std::string& _id)
{
	return mScenes[_id];
}

void SceneManager::SetStartScene(const std::string& _id)
{
	mCurrentScene = _id;
	mNextScene = _id;
}

