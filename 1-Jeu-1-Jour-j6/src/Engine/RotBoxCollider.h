#pragma once
#include "Collider.h"
#include <iostream>

class RotBoxCollider : public Collider
{
private:
    float m_width;
    float m_height;
    float m_rotation;
    Vector2f m_center;
    Vector2f mPivotOffset;

public:
    RotBoxCollider(float width, float height, CollisionLayer layer, uint32_t mask, float rot = 0.f) : Collider(ColliderType::RotRectangle, layer, mask), m_width(width), m_height(height), m_rotation(rot) {}

    bool IsColliding(Collider* other) override;

    void Draw(sf::RenderWindow* _window) override;

    void SetBox(float _width, float _height);

    float GetWidth() { return m_width; }
    float GetHeight() { return m_height; }

    float GetLeft() override;
    float GetRight() override;
    float GetTop() override;
    float GetBottom() override;

    void SetRotation(float _rot) { m_rotation = _rot; }
    void AddRotation(float _rotPlus) { m_rotation += _rotPlus; }
    float GetRotation() { return m_rotation; }

    void SetPivot(float x, float y) { mPivotOffset = { x, y }; }

    void SetRotationCenter(Vector2f rotCen) { m_center = rotCen; }
    void SetRotationCenter(float rotCenX, float rotCenY) { m_center = {rotCenX, rotCenY}; }
    Vector2f GetRotationCenter() { return m_center; }


    std::vector<Vector2f> GetCorners() const;
    std::pair<float, float> Project(const std::vector<Vector2f>& corners, const Vector2f& axis) const;
    bool OverLapOnAxis(const std::vector<Vector2f>& a, const std::vector<Vector2f>& b, const Vector2f& axis) const;

    Vector2f GetMTV(Collider* other);
};

