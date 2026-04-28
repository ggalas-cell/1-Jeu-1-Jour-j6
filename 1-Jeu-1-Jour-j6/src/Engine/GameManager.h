#pragma once

#include <list>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#define FIXED_DT 1.f/200.f
class Entity;
class Scene;
class Debug;

namespace sf 
{
	class RenderWindow;
	class Event;
}

class GameManager
{
	//std::list<Entity*> mEntities;
	//std::list<Entity*> mEntitiesToDestroy;
	//std::list<Entity*> mEntitiesToAdd;

	sf::RenderWindow* mpWindow;
	sf::Font mFont;

	//Scene* mpScene;

	float mDeltaTime;
	float mAccumulateDt;

	int mWindowWidth;
	int mWindowHeight;

	sf::Color mClearColor;

	int mFPS;


private:
	GameManager();

	
	void Update();
	void FixedUpdate();

	void Draw();

	void SetDeltaTime(float deltaTime) { mDeltaTime = deltaTime; }
	void CreateWindow(unsigned int width, unsigned int height, const char* title, int fpsLimit = 60, sf::Color clearColor = sf::Color::Black);



public:
	~GameManager();
	static GameManager* Get();
	sf::RenderWindow* GetWindow() const { return mpWindow; }

	void Init(const char* _title, int _width, int _height, int _targetFPS);
	void Run();
	void TerminateGame();

	float GetWindowWidth() { return mWindowWidth; };
	float GetWindowHeight() { return mWindowHeight; };

	float GetFixedDT() const { return FIXED_DT; }
	float GetDeltaTime() const { return mDeltaTime; }
	sf::Font& GetFont() { return mFont; };

	friend Debug;
	friend Scene;
};