#pragma once

#include "Component.h"
#include "Updatable.h"
#include "FixedUpdatable.h"
#include "Drawable.h"
#include <vector>

namespace sf 
{
	class Shape;
    class Color;
}

class Scene;

class Entity : public Updatable, public FixedUpdatable, public Drawable
{
	std::vector<Component*> mComponents;
	bool mToDestroy = false;

public:
	Entity() = default;
	~Entity();
	friend class Scene;

	template<typename T, typename... Args>
	T* AddComponent(Args&& ...args)
	{
		static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");

		T* component = new T(std::forward<Args>(args)...);
		mComponents.push_back(component);
		component->SetOwner(this);
		return component;
	}

	template<typename T>
	T* GetComponent()
	{
		for (Component* c : mComponents)
		{
			if (auto cast = dynamic_cast<T*>(c))
				return cast;
		}

		return nullptr;
	}

	template<typename T>
	std::vector<T*> GetAllComponents()
	{
		std::vector<T*> result;

		for (Component* c : mComponents)
		{
			if (auto cast = dynamic_cast<T*>(c))
				result.push_back(cast);
		}

		return result;
	}

	void Update() override;
	void FixedUpdate() override;
	void Draw(sf::RenderWindow* _window) override;

	void Destroy();
	bool ToDestroy() const { return mToDestroy; }



//protected:
//	bool mRigidBody = false;
//




public:
	float GetDeltaTime() const;
};
