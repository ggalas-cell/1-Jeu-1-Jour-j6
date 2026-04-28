#include "Collider.h"

Collider::Collider(ColliderType _type, CollisionLayer _layer, uint32_t _mask)
{
    m_type = _type;
    m_id = 0;
    m_offsetX = 0;
    m_offsetY = 0;

    m_isActived = true;
    m_isVisible = false;

    m_layer = _layer;
    m_mask = _mask;
}

bool Collider::CanCollide(Collider* _other)
{
    return (m_mask & _other->m_layer) != 0 && (_other->m_mask & m_layer) != 0;
}

void Collider::SetOffset(float _ox, float _oy)
{
    m_offsetX = _ox;
    m_offsetY = _oy;
}
