#include "RotBoxCollider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "Debug.h"
#include "Entity.h"
#include "Vector2f.h"
#include "CollisionSystem.h"
#include "TransformComponent.h"
#include <iostream>

static constexpr float DEG2RAD = 3.1415925f / 180.f;

bool RotBoxCollider::IsColliding(Collider* other)
{
    if (m_isActived == false || other->IsActived() == false)
        return false;

    if (other->GetType() == ColliderType::RotRectangle)
    {
        RotBoxCollider* r = static_cast<RotBoxCollider*>(other);

        std::vector<Vector2f> cornersA = GetCorners();
        std::vector<Vector2f> cornersB = r->GetCorners();

        float radA = m_rotation * DEG2RAD;
        float radB = r->GetRotation() * DEG2RAD;

        std::vector<Vector2f> axes = {
            Vector2f(std::cos(radA),  std::sin(radA)),
            Vector2f(-std::sin(radA),  std::cos(radA)),
            Vector2f(std::cos(radB),  std::sin(radB)),
            Vector2f(-std::sin(radB),  std::cos(radB)),
        };

        for (Vector2f& axis : axes)
            if (!OverLapOnAxis(cornersA, cornersB, axis))
                return false;

        return true;
    }
    else if (other->GetType() == ColliderType::Rectangle)
    {
        BoxCollider* b = static_cast<BoxCollider*>(other);

        std::vector<Vector2f> cornersA = GetCorners();

        std::vector<Vector2f> cornersB = {
            {b->GetLeft(), b->GetTop()},
            {b->GetRight(), b->GetTop()},
            {b->GetRight(), b->GetBottom()},
            {b->GetLeft(), b->GetBottom()}
        };

        float radA = m_rotation * DEG2RAD;

        std::vector<Vector2f> axes = {
            {std::cos(radA), std::sin(radA)},
            {-std::sin(radA), std::cos(radA)},
            {1, 0},
            {0, 1}
        };

        for (Vector2f& axis : axes)
            if (!OverLapOnAxis(cornersA, cornersB, axis))
                return false;

        return true;
    }
    else // Circle
    {
        CircleCollider* c = static_cast<CircleCollider*>(other);
        Vector2f circlePos = c->GetOwner()->GetComponent<TransformComponent>()->GetPos()
            + c->GetOffset();
        float radius = c->GetRadius();

        // Transformer le centre du cercle dans l'espace local du OBB
        float cx = circlePos.x - (mOwner->GetComponent<TransformComponent>()->GetPos().x + m_offsetX);
        float cy = circlePos.y - (mOwner->GetComponent<TransformComponent>()->GetPos().y + m_offsetY);

        float rad = -m_rotation * DEG2RAD;
        float cosA = std::cos(rad);
        float sinA = std::sin(rad);

        float localX = cx * cosA - cy * sinA;
        float localY = cx * sinA + cy * cosA;

        float hw = m_width * 0.5f;
        float hh = m_height * 0.5f;

        float closestX = std::max(-hw, std::min(localX, hw));
        float closestY = std::max(-hh, std::min(localY, hh));

        float dx = localX - closestX;
        float dy = localY - closestY;

        return dx * dx + dy * dy <= radius * radius;
    }
}

void RotBoxCollider::Draw(sf::RenderWindow* _window)
{

    if (m_isVisible == false)
        return;

    std::vector<Vector2f> corners = GetCorners();

    for (int i = 0; i < 4; ++i)
    {

        Vector2f& a = corners[i];
        Vector2f& b = corners[(i + 1) % 4];
        Debug::DrawLine(a.x, a.y, b.x, b.y, sf::Color::Green);
    }
}

void RotBoxCollider::SetBox(float _width, float _height)
{
    m_width = _width;
    m_height = _height;
}

float RotBoxCollider::GetLeft()
{
    Vector2f pos = mOwner->GetComponent<TransformComponent>()->GetPos();
    return pos.GetX() + m_offsetX - m_width * 0.5f;
}

float RotBoxCollider::GetRight()
{
    Vector2f pos = mOwner->GetComponent<TransformComponent>()->GetPos();
    return pos.GetX() + m_offsetX + m_width * 0.5f;
}

float RotBoxCollider::GetTop()
{
    Vector2f pos = mOwner->GetComponent<TransformComponent>()->GetPos();
    return pos.GetY() + m_offsetY - m_height * 0.5f;
}

float RotBoxCollider::GetBottom()
{
    Vector2f pos = mOwner->GetComponent<TransformComponent>()->GetPos();
    return pos.GetY() + m_offsetY + m_height * 0.5f;
}


std::vector<Vector2f> RotBoxCollider::GetCorners() const
{
    Vector2f pos = mOwner->GetComponent<TransformComponent>()->GetPos();

    float rad = m_rotation * DEG2RAD;
    float cosA = std::cos(rad);
    float sinA = std::sin(rad);

    float hw = m_width * 0.5f;
    float hh = m_height * 0.5f;

    // Coins locaux relatifs au pivot
    std::vector<Vector2f> local = {
        Vector2f(-hw - mPivotOffset.x, -hh - mPivotOffset.y),
        Vector2f(hw - mPivotOffset.x, -hh - mPivotOffset.y),
        Vector2f(hw - mPivotOffset.x,  hh - mPivotOffset.y),
        Vector2f(-hw - mPivotOffset.x,  hh - mPivotOffset.y)
    };

    // Pivot en world space
    float px = pos.x + m_offsetX + mPivotOffset.x;
    float py = pos.y + m_offsetY + mPivotOffset.y;

    std::vector<Vector2f> world;
    for (Vector2f& l : local)
    {
        world.push_back(Vector2f(
            px + l.x * cosA - l.y * sinA,
            py + l.x * sinA + l.y * cosA
        ));
    }
    return world;
}

std::pair<float, float> RotBoxCollider::Project(const std::vector<Vector2f>& corners, const Vector2f& axis) const
{
    float min = 1e30f, max = -1e30f;
    for (const Vector2f& c : corners)
    {
        float d = c.x * axis.x + c.y * axis.y;
        min = std::min(min, d);
        max = std::max(max, d);
    }
    return { min, max };
}

bool RotBoxCollider::OverLapOnAxis(const std::vector<Vector2f>& a, const std::vector<Vector2f>& b, const Vector2f& axis) const
{
    auto [minA, maxA] = Project(a, axis);
    auto [minB, maxB] = Project(b, axis);
    return maxA >= minB && maxB >= minA;
}

Vector2f RotBoxCollider::GetMTV(Collider* other)
{
    std::vector<Vector2f> cornersA = GetCorners();

    std::vector<Vector2f> cornersB;
    std::vector<Vector2f> axes;

    float radA = m_rotation * DEG2RAD;
    axes.push_back(Vector2f(std::cos(radA), std::sin(radA)));
    axes.push_back(Vector2f(-std::sin(radA), std::cos(radA)));

    if (other->GetType() == ColliderType::RotRectangle)
    {
        RotBoxCollider* rot = static_cast<RotBoxCollider*>(other);
        cornersB = rot->GetCorners();

        float radB = rot->GetRotation() * DEG2RAD;
        axes.push_back(Vector2f(std::cos(radB), std::sin(radB)));
        axes.push_back(Vector2f(-std::sin(radB), std::cos(radB)));
    }
    else if (other->GetType() == ColliderType::Rectangle)
    {
        BoxCollider* box = static_cast<BoxCollider*>(other);
        cornersB = {
            Vector2f(box->GetLeft(),  box->GetTop()),
            Vector2f(box->GetRight(), box->GetTop()),
            Vector2f(box->GetRight(), box->GetBottom()),
            Vector2f(box->GetLeft(),  box->GetBottom())
        };

        axes.push_back(Vector2f(1, 0));
        axes.push_back(Vector2f(0, 1));
    }
    else if (other->GetType() == ColliderType::Circle)
    {
        CircleCollider* circle = static_cast<CircleCollider*>(other);
        Vector2f circlePos = circle->GetOwner()->GetComponent<TransformComponent>()->GetPos()
            + circle->GetOffset();

        // Trouver le coin le plus proche pour l'axe supplémentaire
        std::vector<Vector2f> corners = GetCorners();
        float minDist = 1e30f;
        Vector2f closest;
        for (Vector2f& c : corners)
        {
            float dx = c.x - circlePos.x;
            float dy = c.y - circlePos.y;
            float dist = dx * dx + dy * dy;
            if (dist < minDist)
            {
                minDist = dist;
                closest = c;
            }
        }

        // Axe du coin le plus proche vers le centre du cercle
        Vector2f cornerAxis = Vector2f(circlePos.x - closest.x, circlePos.y - closest.y);
        float len = std::sqrt(cornerAxis.x * cornerAxis.x + cornerAxis.y * cornerAxis.y);
        if (len > 0.0001f)
            axes.push_back(Vector2f(cornerAxis.x / len, cornerAxis.y / len));

        // Coins du cercle = un seul point (centre), la projection utilise le rayon
        // On génère 4 points fictifs autour du centre
        float r = circle->GetRadius();
        cornersB = {
            Vector2f(circlePos.x - r, circlePos.y),
            Vector2f(circlePos.x + r, circlePos.y),
            Vector2f(circlePos.x, circlePos.y - r),
            Vector2f(circlePos.x, circlePos.y + r)
        };
    }
    else
        return Vector2f(0.f, 0.f);

    float minOverlap = 1e30f;
    Vector2f mtvAxis;

    for (Vector2f& axis : axes)
    {
        auto [minA, maxA] = Project(cornersA, axis);
        auto [minB, maxB] = Project(cornersB, axis);

        float overlap = std::min(maxA, maxB) - std::max(minA, minB);
        if (overlap <= 0.f) return Vector2f(0.f, 0.f);

        if (overlap < minOverlap)
        {
            minOverlap = overlap;
            mtvAxis = axis;
        }
    }

    Vector2f posA = mOwner->GetComponent<TransformComponent>()->GetPos();
    Vector2f posB = other->GetOwner()->GetComponent<TransformComponent>()->GetPos();
    Vector2f dir(posA.GetX() - posB.GetX(), posA.GetY() - posB.GetY());

    if (dir.GetX() * mtvAxis.GetX() + dir.GetY() * mtvAxis.GetY() < 0.f)
        mtvAxis = Vector2f(-mtvAxis.GetX(), -mtvAxis.GetY());

    return Vector2f(mtvAxis.GetX() * minOverlap, mtvAxis.GetY() * minOverlap);
}