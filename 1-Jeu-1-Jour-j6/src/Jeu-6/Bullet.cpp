#include "Bullet.h"
#include "GameManager.h"
#include "TransformComponent.h"
#include "TagComponent.h"
#include "Health.h"
#include "Entity.h"
#include "Collider.h"
#include "GameData.h"

void Bullet::FixedUpdate()
{
	m_lifetime = GameData::Get()->BulletLifetime;
	float deltatime = GameManager::Get()->GetFixedDT();
	m_lifetimeTimer += deltatime;

	if (m_lifetimeTimer >= m_lifetime)
	{
		mOwner->Destroy();
		return;
	}
	TransformComponent* transform = mOwner->GetComponent<TransformComponent>();

	if (transform)
	{
		Vector2f pos = transform->GetPos();

		pos.x += m_direction.x * m_speed * deltatime;
		pos.y += m_direction.y * m_speed * deltatime;
		transform->SetPos(pos);
	}

}

void Bullet::OnCollisionEnter(Collider* _self, Collider* _other)
{
	TagComponent* tag = _other->GetOwner()->GetComponent<TagComponent>();
	if (!tag) return;
	if (tag->Is("Player")) return;

	Health* hp = _other->GetOwner()->GetComponent<Health>();
	hp->TakeDamage(m_damage);
	mOwner->Destroy();
}
