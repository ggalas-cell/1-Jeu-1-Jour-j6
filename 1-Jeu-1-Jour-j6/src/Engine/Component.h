#pragma once

class Entity;

class Component
{
protected:
	Entity* mOwner;

public:
	Component();
	virtual ~Component();

	void SetOwner(Entity* _owner) { mOwner = _owner; }
	Entity* GetOwner() { return mOwner; }
};

