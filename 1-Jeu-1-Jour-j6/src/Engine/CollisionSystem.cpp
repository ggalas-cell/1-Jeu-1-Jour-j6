#include "CollisionSystem.h"
#include "Entity.h"
#include "Collider.h"
#include "Collidable.h"
#include "BoxCollider.h"
#include "RotBoxCollider.h"
#include <iostream>
CollisionSystem* CollisionSystem::instance = nullptr;

CollisionSystem* CollisionSystem::Get()
{
    if (instance == nullptr) {
        instance = new CollisionSystem();
    }
    return instance;
}

bool SamePair(const CollisionInfo& c1, Collider* a, Collider* b)
{
    return (c1.a == a && c1.b == b) || (c1.a == b && c1.b == a);
}

bool WasColliding(const std::vector<CollisionInfo>& list, Collider* a, Collider* b)
{
    for (const CollisionInfo& c : list)
    {
        if (SamePair(c, a, b))
            return true;
    }

    return false;
}

CollisionSide CheckCollisionSide(Collider* a, Collider* b) {

    if (a->GetType() == ColliderType::RotRectangle || b->GetType() == ColliderType::RotRectangle)
    {
        RotBoxCollider* rot = (a->GetType() == ColliderType::RotRectangle)
            ? static_cast<RotBoxCollider*>(a)
            : static_cast<RotBoxCollider*>(b);

        Collider* other = (a->GetType() == ColliderType::RotRectangle) ? b : a;

        Vector2f mtv = rot->GetMTV(other);

        if (mtv.GetX() == 0.f && mtv.GetY() == 0.f)
            return CollisionSide::None;

        // Si c'est b qui est le RotBox, inverser le MTV pour avoir le côté du point de vue de a
        if (b->GetType() == ColliderType::RotRectangle)
            mtv = Vector2f(-mtv.GetX(), -mtv.GetY());

        if (std::abs(mtv.GetX()) > std::abs(mtv.GetY()))
            return mtv.GetX() > 0.f ? CollisionSide::Right : CollisionSide::Left;
        else
            return mtv.GetY() > 0.f ? CollisionSide::Bottom : CollisionSide::Top;
    }

    // Fallback AABB pour Box/Circle sans rotation
    float overlapLeft = a->GetRight() - b->GetLeft();
    float overlapRight = b->GetRight() - a->GetLeft();
    float overlapTop = a->GetBottom() - b->GetTop();
    float overlapBottom = b->GetBottom() - a->GetTop();
    float min = std::min({ overlapLeft, overlapRight, overlapTop, overlapBottom });

    if (min == overlapLeft)   return CollisionSide::Left;
    if (min == overlapRight)  return CollisionSide::Right;
    if (min == overlapTop)    return CollisionSide::Top;
    if (min == overlapBottom) return CollisionSide::Bottom;
    return CollisionSide::None;
}


void CollisionSystem::FixedUpdate(const std::list<Entity*>& entities)
{
    std::vector<Collider*> colliders;
    std::vector<CollisionInfo> currentCollisions;

    for (Entity* e : entities)
    {
        std::vector<Collider*> cols = e->GetAllComponents<Collider>();
        colliders.insert(colliders.end(), cols.begin(), cols.end());
    }

    for (int i = 0; i < colliders.size(); ++i)
    {
        for (int j = i + 1; j < colliders.size(); ++j)
        {
            Collider* a = colliders[i];
            Collider* b = colliders[j];

            if (a->GetOwner() == b->GetOwner())
                continue;

            if (a->CanCollide(b) == false)
                continue;

            if (a->IsColliding(b) == false)
                continue;

            currentCollisions.push_back({ a, b });

            bool wasColliding = WasColliding(m_previousCollisions, a, b);

            std::vector<Collidable*> aListeners = a->GetOwner()->GetAllComponents<Collidable>();
            std::vector<Collidable*> bListeners = b->GetOwner()->GetAllComponents<Collidable>();

            CollisionSide sideA = CheckCollisionSide(a, b);
            CollisionSide sideB = CheckCollisionSide(b, a);
            a->SetSide(sideB);
            b->SetSide(sideA);

            if (wasColliding == false)
            {
                for (Collidable* c : aListeners)
                    c->OnCollisionEnter(a, b);

                for (Collidable* c : bListeners)
                    c->OnCollisionEnter(b, a);
            }

            for (Collidable* c : aListeners)
                c->OnCollisionStay(a, b);

            for (Collidable* c : bListeners)
                c->OnCollisionStay(b, a);
        }
    }

    for (const CollisionInfo& oldCol : m_previousCollisions)
    {
        if (WasColliding(currentCollisions, oldCol.a, oldCol.b) == false)
        {
            std::vector<Collidable*> aListeners = oldCol.a->GetOwner()->GetAllComponents<Collidable>();
            std::vector<Collidable*> bListeners = oldCol.b->GetOwner()->GetAllComponents<Collidable>();

            for (Collidable* c : aListeners)
                c->OnCollisionExit(oldCol.a, oldCol.b);

            for (Collidable* c : bListeners)
                c->OnCollisionExit(oldCol.b, oldCol.a);
        }
    }

    m_previousCollisions = currentCollisions;
}

void CollisionSystem::Clear(Entity* entity)
{
    std::vector<Collider*> colliders = entity->GetAllComponents<Collider>();

    m_previousCollisions.erase(
        std::remove_if(
            m_previousCollisions.begin(),
            m_previousCollisions.end(),
            [&colliders](const CollisionInfo& info)
            {
                for (Collider* col : colliders)
                {
                    if (info.a == col || info.b == col)
                        return true;
                }
                return false;
            }
        ),
        m_previousCollisions.end()
    );
}