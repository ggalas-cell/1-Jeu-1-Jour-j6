#include "GameManager.h"

#include "Entity.h"
#include "Debug.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "CollisionSystem.h"
#include <iostream>
#include "InputManager.h"
#include "SceneManager.h"
#include "AssetManager.h"
#include "Scene.h"
float timer = 0.0f;
int FPS = 0;
GameManager::GameManager()
{
	mpWindow = nullptr;
	mDeltaTime = 0.0f;
	mWindowWidth = -1;
	mWindowHeight = -1;
}

GameManager* GameManager::Get()
{
	static GameManager mInstance;

	return &mInstance;
}

GameManager::~GameManager()
{
	delete mpWindow;

	//for (Entity* entity : mEntities)
	//{
	//	delete entity;
	//}
}

void GameManager::FixedUpdate() {
	SceneManager* sm = SceneManager::Get();
	CollisionSystem* cs = CollisionSystem::Get();

	cs->FixedUpdate(sm->GetCurrentScene()->GetEntities());
	sm->FixedUpdate();
}

void GameManager::CreateWindow(unsigned int width, unsigned int height, const char* title, int fpsLimit, sf::Color clearColor)
{
	_ASSERT(mpWindow == nullptr);

	mpWindow = new sf::RenderWindow(sf::VideoMode(width, height), title);
	mpWindow->setFramerateLimit(fpsLimit);

	mWindowWidth = width;
	mWindowHeight = height;

	mClearColor = clearColor;
}

void GameManager::Init(const char* _title, int _width, int _height, int _targetFPS)
{
	mFPS = _targetFPS;
	CreateWindow(_width, _height, _title, mFPS);
}

void GameManager::Run()
{
	mpWindow->setMouseCursorVisible(false);

	if (mpWindow == nullptr)
	{
		std::cout << "Window not created, creating default window" << std::endl;
		CreateWindow(1280, 720, "Default window");
	}
	float height = GetWindowHeight();
	float width = GetWindowWidth();

	//#TODO : Load somewhere else
	bool fontLoaded = mFont.loadFromFile("../../res/Hack-Regular.ttf");
	_ASSERT(fontLoaded);


	AssetManager* am = AssetManager::Get();

	am->LoadAssets();

	sf::Clock clock;
	while (mpWindow->isOpen())
	{
		SetDeltaTime(clock.restart().asSeconds());


		mAccumulateDt += mDeltaTime;
		while (mAccumulateDt >= FIXED_DT) {
			FixedUpdate();
			mAccumulateDt -= FIXED_DT;
		}
		timer += mDeltaTime;
		if (timer > 1.0f)
		{
			FPS = (int)(1.0f / mDeltaTime);
			timer = 0.0f;
		}

		//std::cout << "FPS: " + std::to_string(FPS) << std::endl;
		Update();

		Draw();
	}
}



void GameManager::Update()
{
	SceneManager* sm = SceneManager::Get();
	InputManager* im = InputManager::Get();

	im->Update(mpWindow);

	sm->Update();
}

void GameManager::Draw()
{
	mpWindow->clear(mClearColor);

	SceneManager* sm = SceneManager::Get();
	
	sm->Draw(mpWindow);
	
	Debug::Get()->Draw(mpWindow);

	mpWindow->display();
}

void GameManager::TerminateGame() {
	mpWindow->close();
}
