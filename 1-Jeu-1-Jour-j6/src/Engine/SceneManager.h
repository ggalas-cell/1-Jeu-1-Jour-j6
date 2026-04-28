#pragma once
#include <map>
#include <string>
#include "Drawable.h"
#include "Updatable.h"
#include "FixedUpdatable.h"

class Scene;

class SceneManager : public Drawable, public Updatable, public FixedUpdatable
{
private:
	std::map<std::string, Scene*> mScenes;
	std::string mCurrentScene;
	std::string mNextScene;
	bool mChangeScene;

	static SceneManager* instance;
	SceneManager();

public:
	static SceneManager* Get();
	~SceneManager();
	
	Scene* GetCurrentScene();
	std::string GetCurrentSceneID();
	void ChangeScene(const std::string& _id);
	void ReloadScene();
	void Update() override;
	void FixedUpdate() override;
	void Draw(sf::RenderWindow* _window) override;
	void AddScene(const std::string& _id, Scene* _scene);
	Scene* FindSceneById(const std::string& _id);
	void SetStartScene(const std::string& _id);
};

