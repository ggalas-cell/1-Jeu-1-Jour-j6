#pragma once
#include "Component.h"
#include "FixedUpdatable.h"
#include "Vector2f.h"
#include "Collidable.h"

#define PIXEL_PER_METER 100

class Collider;

class Rigidbody2D : public Component, public FixedUpdatable, public Collidable
{
public:
    Rigidbody2D(float mass = 1.0f, bool useGravity = true, float restitution = 0.8f);

    void AddForce(Vector2f force);
    void AddImpulse(Vector2f impulse);

    void SetVelocity(const Vector2f& vel);
    Vector2f GetVelocity() const;

    void SetKinematic(bool _value) { m_isKinematic = _value; }
    bool IsKinematic() { return m_isKinematic; }
    void SetSafeMargin(float _safeMargin) { m_safeMargin = _safeMargin; }
    void SetGravity(Vector2f _g) { m_gravity = _g; }
    void SetMass(float _mass) { m_mass = _mass; }
    void SetRestitution(float _rest) { m_restitution = _rest; }

    void FixedUpdate() override;

    void OnCollisionStay(Collider* _self, Collider* _other) override;

private:
    float m_mass;
    bool m_useGravity;
    float m_restitution;
    bool m_isKinematic;

    float m_safeMargin;

    Vector2f m_velocity;
    Vector2f m_acceleration;
    Vector2f m_gravity;
};