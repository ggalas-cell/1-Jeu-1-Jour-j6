#pragma once
#include "Collider.h"

class BoxCollider : public Collider
{
private:
    float m_width;
    float m_height;

public:
    BoxCollider(float width, float height, CollisionLayer layer, uint32_t mask) : Collider(ColliderType::Rectangle, layer, mask), m_width(width), m_height(height) {}

    bool IsColliding(Collider* other) override;

    void Draw(sf::RenderWindow* _window) override;

    void SetBox(float _width, float _height);

    float GetWidth() { return m_width; }
    float GetHeight() { return m_height; }

    float GetLeft() override;
    float GetRight() override;
    float GetTop() override;
    float GetBottom() override;
};