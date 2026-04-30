#pragma once
#include "Component.h"
#include "Updatable.h"
#include "Collidable.h"
#include "FixedUpdatable.h"
#include "Vector2f.h"

class Bullet : public Component ,public FixedUpdatable,public Collidable
{
    Vector2f m_direction;
    float    m_speed = 300.f;
    float    m_fequency = 0.8f;
    int      m_damage = 1;
    float    m_lifetime = 0.f;
    float    m_lifetimeTimer = 0.f;


public:
    void SetDirection(Vector2f dir) { m_direction = dir; }
    void SetSpeed(float speed) { m_speed = speed; }
    void SetFrequency(float frequency) { m_fequency = frequency; }
    void SetDamage(int damage) { m_damage = damage; }
    void SetLifetime(float t) { m_lifetime = t; }

    void FixedUpdate() override;
    void OnCollisionEnter(Collider* _self, Collider* _other) override;
};
