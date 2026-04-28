#pragma once
#include <list>
#include <vector>
#include <Collider.h>

class Entity;
class Collider;

struct CollisionInfo
{
    Collider* a;
    Collider* b;
};

class CollisionSystem
{
private:
    std::vector<CollisionInfo> m_previousCollisions;
    static CollisionSystem* instance;
    CollisionSystem() {};

public:
    static CollisionSystem* Get();


    void FixedUpdate(const std::list<Entity*>& entities);
    void Clear(Entity* entity);
    void ClearAll() { m_previousCollisions.clear(); }
};
CollisionSide CheckCollisionSide(Collider* a, Collider* b);
