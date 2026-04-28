#pragma once
#include "Collider.h"

class CircleCollider : public Collider
{
private:
    float m_radius;

public:
    CircleCollider(float radius, CollisionLayer layer, uint32_t mask) : Collider(ColliderType::Circle, layer, mask), m_radius(radius) {}

    float GetRadius() const { return m_radius; }

    bool IsColliding(Collider* other) override;
    void Draw(sf::RenderWindow* _window) override;

    void SetRadius(float _radius);

    float GetLeft() override;
    float GetRight() override;
    float GetTop() override;
    float GetBottom() override;
};