#pragma once
#include "Updatable.h"
#include "Drawable.h"
#include "Entity.h"
#include <vector>
#include <list>
#include <string>

class GameManager;


namespace
{
	class RenderWindow;
}


class Scene : public Updatable, public FixedUpdatable, public Drawable
{
private:
	std::list<Entity*> mEntities;
	
	std::list<Entity*> mEntitiesToDestroy;
	std::list<Entity*> mEntitiesToAdd;

	GameManager* mpGameManager;

private:
	void SetGameManager(GameManager* pGameManager) { mpGameManager = pGameManager; }
	void Update() override;
	void FixedUpdate() override;
	void Draw(sf::RenderWindow* _window);
	
public:
	Scene() = default;
	~Scene();

	virtual void OnUpdate() = 0;
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;

	virtual void Create(const std::string& entity, float _posX, float _posY, int _width, int _height, float _rot) = 0;
	virtual void OnDraw(sf::RenderWindow* _window) {}


	float GetDeltaTime() const;
	int GetWindowWidth() const;
	int GetWindowHeight() const;

	friend GameManager;

	Entity* CreateEntity();
	void DestroyEntity(Entity* _ent);
	void DestroyAllEntitiesWithTag(const std::string& _tag);
	void DestroyAllEntities();
	void DestroyEntitiesNow();

	std::list<Entity*> GetEntities() { return mEntities; }

	Entity* FindByTag(const std::string& _tag);
	std::list<Entity*> FindAllEntitiesWithTag(const std::string& _tag);

	friend class SceneManager;
};
