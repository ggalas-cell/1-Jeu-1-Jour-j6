#include "Health.h"
#include "Entity.h"

Health::Health(int currenthp, int maxhp) :
    m_currentHp(currenthp), m_MaxHp(maxhp) , m_IsDead(false) {}

bool Health::IsDead()
{
    if (m_currentHp <= 0) m_IsDead = true;
    return m_IsDead;
}

void Health::Kill()
{
    m_currentHp = 0;
    IsDead();
    if (OnDeath) OnDeath();
    else mOwner->Destroy();
}

void Health::TakeDamage(int dmg)
{
    if (IsDead()) return;
    m_currentHp -= dmg;

    if (m_currentHp <= 0) { m_currentHp = 0; Kill(); return; }
}
