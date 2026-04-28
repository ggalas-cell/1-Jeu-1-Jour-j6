#pragma once
#include "Component.h"
#include "Updatable.h"
#include <functional>

class Health : public Component, public Updatable 
{
	int m_currentHp;
	int m_MaxHp;
	bool m_IsDead;

	std::function<void()> OnDeath = nullptr;
public:
	Health(int currenthp, int maxhp);

	bool IsDead();
	void Kill();
	
	void TakeDamage(int dmg);
};

