#include "BoxCollider.h"
#include "CircleCollider.h"
#include "Debug.h"
#include "Entity.h"
#include "Vector2f.h"
#include "CollisionSystem.h"
#include "TransformComponent.h"
#include <iostream>

bool BoxCollider::IsColliding(Collider* other)
{
    if (m_isActived == false || other->IsActived() == false)
        return false;

    if (other->GetType() == ColliderType::Rectangle)
    {
        BoxCollider* r = static_cast<BoxCollider*>(other);

        return !(GetRight() < r->GetLeft() ||
            GetLeft() > r->GetRight() ||
            GetBottom() < r->GetTop() ||
            GetTop() > r->GetBottom());
    }
    else if (other->GetType() == ColliderType::RotRectangle)
    {
        return other->IsColliding(this);
    }
    else // Circle
    {
        CircleCollider* c = (CircleCollider*)other;

        Vector2f pos = c->GetOwner()->GetComponent<TransformComponent>()->GetPos();
        float radius = c->GetRadius();

        // clamp du point du cercle dans le rectangle
        float closestX = std::max(GetLeft(), std::min(pos.GetX(), GetRight()));
        float closestY = std::max(GetTop(), std::min(pos.GetY(), GetBottom()));

        float dx = closestX - pos.x;
        float dy = closestY - pos.y;

        return dx * dx + dy * dy <= radius * radius;
    }
}

void BoxCollider::Draw(sf::RenderWindow* _window)
{
    if (m_isVisible == false)
        return;

    Vector2f pos = mOwner->GetComponent<TransformComponent>()->GetPos();

    Debug::DrawRectangle(pos.x + m_offsetX - m_width * 0.5f, pos.y + m_offsetY - m_height * 0.5f, m_width, m_height, sf::Color::Red);
}

void BoxCollider::SetBox(float _width, float _height)
{
    m_width = _width;
    m_height = _height;
}

float BoxCollider::GetLeft()
{
    Vector2f pos = mOwner->GetComponent<TransformComponent>()->GetPos();
    return pos.GetX() + m_offsetX - m_width * 0.5f;
}

float BoxCollider::GetRight()
{
    Vector2f pos = mOwner->GetComponent<TransformComponent>()->GetPos();
    return pos.GetX() + m_offsetX + m_width * 0.5f;
}

float BoxCollider::GetTop()
{
    Vector2f pos = mOwner->GetComponent<TransformComponent>()->GetPos();
    return pos.GetY() + m_offsetY - m_height * 0.5f;
}

float BoxCollider::GetBottom()
{
    Vector2f pos = mOwner->GetComponent<TransformComponent>()->GetPos();
    return pos.GetY() + m_offsetY + m_height * 0.5f;
}