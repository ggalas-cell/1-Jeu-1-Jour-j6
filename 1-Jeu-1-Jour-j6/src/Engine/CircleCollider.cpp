#include "CircleCollider.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "Vector2f.h"
#include "Debug.h"

#define M_PI 3.14159265358979323846

bool CircleCollider::IsColliding(Collider* _target)
{
    if (m_isActived == false || _target->IsActived() == false)
        return false;

    if (_target->GetType() == ColliderType::Circle)
    {
        CircleCollider* c = (CircleCollider*)_target;

        Vector2f pos = mOwner->GetComponent<TransformComponent>()->GetPos();
        Vector2f targetPos = c->GetOwner()->GetComponent<TransformComponent>()->GetPos();

        float dx = targetPos.GetX() - pos.GetX();
        float dy = targetPos.GetX() - pos.GetY();
        float r = m_radius + c->m_radius;

        return dx * dx + dy * dy <= r * r;
    }
    else if (_target->GetType() == ColliderType::RotRectangle)
    {
        return _target->IsColliding(this);
    }
    else // Rectangle
    {
        return _target->IsColliding(this);
    }
}

void CircleCollider::Draw(sf::RenderWindow* _window)
{
    if (m_isVisible == false)
        return;

    Vector2f pos = mOwner->GetComponent<TransformComponent>()->GetPos();
    pos.SetValue(pos.GetX() + m_offsetX, pos.GetY() + m_offsetY);

    Debug::DrawCircle(pos.x, pos.y, m_radius, sf::Color::Blue);
}

void CircleCollider::SetRadius(float _radius)
{
    m_radius = _radius;
}

float CircleCollider::GetLeft()
{
    Vector2f pos = mOwner->GetComponent<TransformComponent>()->GetPos();
    return pos.GetX() + m_offsetX - m_radius;
}

float CircleCollider::GetRight()
{
    Vector2f pos = mOwner->GetComponent<TransformComponent>()->GetPos();
    return pos.GetX() + m_offsetX + m_radius;
}

float CircleCollider::GetTop()
{
    Vector2f pos = mOwner->GetComponent<TransformComponent>()->GetPos();
    return pos.GetY() + m_offsetY - m_radius;
}

float CircleCollider::GetBottom()
{
    Vector2f pos = mOwner->GetComponent<TransformComponent>()->GetPos();
    return pos.GetY() + m_offsetY + m_radius;
}