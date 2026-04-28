#pragma once
#include "Component.h"
#include "Drawable.h"
#include "Vector2f.h"
#include <string>
#include <SFML/System/Vector2.hpp>

enum ColliderType
{
    Rectangle,
    Circle,
    RotRectangle
};

enum CollisionLayer;

enum CollisionSide {
    None,
    Top,
    Bottom,
    Left,
    Right,

    Count
};

class Collider : public Component, public Drawable
{
protected:
    float m_offsetX;
    float m_offsetY;
    ColliderType m_type;
    int m_id;

    bool m_isActived;
    bool m_isVisible;
    bool m_isTrigger;

    CollisionLayer m_layer;
    uint32_t m_mask;

    CollisionSide mSide;
    
public:
    Collider(ColliderType _type, CollisionLayer layer, uint32_t _mask);
    virtual ~Collider() {}

    ColliderType GetType() const { return m_type; }

    CollisionLayer GetLayer() { return m_layer; }
    bool CanCollide(Collider* _other);

    void SetOffset(float _ox, float _oy);
    Vector2f GetOffset() { Vector2f offset(m_offsetX, m_offsetY); return offset; }

    void SetActive(bool _value) { m_isActived = _value; }
    bool IsActived() { return m_isActived; }

    void SetVisible(bool _value) { m_isVisible = _value; }
    bool IsVisible() { return m_isVisible; }

    void SetTrigger(bool _value) { m_isTrigger = _value; }
    bool IsTrigger() { return m_isTrigger; }

    uint32_t GetMask() { return m_mask; }

    void SetId(int _id) { m_id = _id; }
    int GetId() { return m_id; }

    virtual bool IsColliding(Collider* other) = 0;

    virtual float GetLeft() = 0;
    virtual float GetRight() = 0;
    virtual float GetTop() = 0;
    virtual float GetBottom() = 0;

    void SetSide(CollisionSide newSide) { mSide = newSide; }
    CollisionSide GetSide() { return mSide; }
};