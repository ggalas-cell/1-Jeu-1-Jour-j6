#include "Bullet.h"
#include "GameManager.h"
#include "TransformComponent.h"
#include "TagComponent.h"
#include "Health.h"
#include "Entity.h"
#include "Collider.h"

void Bullet::Shoot()
{
	float deltatime = GameManager::Get()->GetDeltaTime();
	m_lifetimeTimer += deltatime;

	TransformComponent* transform = mOwner->AddComponent<TransformComponent>();

	if (transform)
	{
		Vector2f pos = transform->GetPos();

		pos.x = m_direction.x * m_speed * deltatime;
		pos.y = m_direction.y * m_speed * deltatime;
		transform->SetPos(pos);
	}

}

void Bullet::FixedUpdate()
{
	Shoot();
}

void Bullet::OnCollisionEnter(Collider* _self, Collider* _other)
{
	TagComponent* tag = _other->GetOwner()->GetComponent<TagComponent>();

	if (tag->Is("Enemy")) return;

	Health* hp = _other->GetOwner()->GetComponent<Health>();
	hp->TakeDamage(m_damage);
	mOwner->Destroy();
}
