#pragma once
#include "Component.h"
#include "Updatable.h"
#include "FixedUpdatable.h"
#include "Vector2f.h"
#include <functional>

class ShootingComponent : public Component , public Updatable , public FixedUpdatable
{
    float m_fireTimer;
    
    bool m_shootLeft = false;
    bool m_shootRight = false;
    bool m_shootUp = false;
    bool m_shootDown = false;

    std::function<void(Vector2f, Vector2f)>m_spawnBullet;

public:
    void SetSpawnCallback(std::function<void(Vector2f, Vector2f)>callback) { m_spawnBullet = callback; }

    void Update() override;
    void FixedUpdate() override;

private:
    void TryShoot(Vector2f direction);
};


