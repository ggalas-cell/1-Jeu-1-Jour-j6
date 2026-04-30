#include "ShootingComponent.h"
#include <InputManager.h>
#include <GameData.h>
#include <GameManager.h>
#include "Entity.h"
#include <TransformComponent.h>

void ShootingComponent::Update()
{
    InputManager* input = InputManager::Get();
    m_shootLeft = input->IsKeyHeld(sf::Keyboard::Left);
    m_shootRight = input->IsKeyHeld(sf::Keyboard::Right);
    m_shootUp = input->IsKeyHeld(sf::Keyboard::Up);
    m_shootDown = input->IsKeyHeld(sf::Keyboard::Down);
}

void ShootingComponent::FixedUpdate()
{
   float frequency = GameData::Get()->FireFrequency;
    m_fireTimer += GameManager::Get()->GetFixedDT();

    if (m_fireTimer < frequency) return;

    if (m_shootLeft) { TryShoot(Vector2f(-1.f, 0.f)); m_fireTimer = 0.f; }
    if (m_shootRight) { TryShoot(Vector2f(1.f, 0.f)); m_fireTimer = 0.f; }
    if (m_shootUp) { TryShoot(Vector2f(0.f, -1.f)); m_fireTimer = 0.f; }
    if (m_shootDown) { TryShoot(Vector2f(0.f, 1.f)); m_fireTimer = 0.f; }
}

void ShootingComponent::TryShoot(Vector2f direction)
{
    if (!m_spawnBullet) return;
    Vector2f pos = mOwner->GetComponent<TransformComponent>()->GetPos();
    m_spawnBullet(pos, direction);
}
