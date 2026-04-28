#include "Player.h"
#include "InputManager.h"
#include "Rigidbody2D.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "TagComponent.h"
#include "Collider.h"
#include "PushBlock.h"
#include "GameData.h"
#include <iostream>
#include <functional>

Player::Player()
{
    m_sqeed =GameData::Get()->PlayerSpeed;

    m_moveLeftKey = sf::Keyboard::Key::Q;
    m_moveRightKey = sf::Keyboard::Key::D;
    m_moveUpKey = sf::Keyboard::Key::Z;
    m_moveDownKey = sf::Keyboard::Key::S;

    m_ShootUpKey = sf::Keyboard::Key::Up;
    m_ShootDownKey = sf::Keyboard::Key::Down;
    m_ShootLeftKey = sf::Keyboard::Key::Left;
    m_ShootRightKey = sf::Keyboard::Key::Right;
    m_ReloadKey = sf::Keyboard::Key::R;

    mMovingLeft = false;
    mMovingRight = false;
    mMovingUp = false;
    mMovingDown = false;

    mShootingUp = false;
    mShootingDown = false;
    mShootingLeft = false;
    mShootingRight = false;
    mReloading = false;
}

Vector2f Player::GetMoveDirection() const
{
    Vector2f dir;
    if (mMovingLeft)  dir.x -= 1.f;
    if (mMovingRight) dir.x += 1.f;
    if (mMovingUp)    dir.y -= 1.f;
    if (mMovingDown)  dir.y += 1.f;

    return dir;
}

void Player::Update()
{
    InputManager* input = InputManager::Get();
    mMovingLeft = input->IsKeyHeld(m_moveLeftKey);
    mMovingRight = input->IsKeyHeld(m_moveRightKey);
    mMovingUp = input->IsKeyHeld(m_moveUpKey);
    mMovingDown = input->IsKeyHeld(m_moveDownKey);
}

void Player::FixedUpdate()
{
    Rigidbody2D* rb = mOwner->GetComponent<Rigidbody2D>();
    Vector2f velocity;

    if (mMovingLeft)  velocity.x = -m_sqeed * 300;
    if (mMovingRight) velocity.x = m_sqeed * 300;
    if (mMovingUp)    velocity.y = -m_sqeed * 300;
    if (mMovingDown)  velocity.y = m_sqeed * 300;

    rb->SetVelocity(velocity);
}

void Player::OnCollisionEnter(Collider* _self, Collider* _other)
{
    Entity* other = _other->GetOwner();
    if (!other) return;
    TagComponent* tag = other->GetComponent<TagComponent>();
    if (!tag) return;

    if (tag->Is("Block"))
    {
        PushBlock* block = other->GetComponent<PushBlock>();
        if (block)
        {
            Vector2f dir = GetMoveDirection();
            //std::cout << "[Player] Push bloc dir=(" << dir.x << "," << dir.y << ")\n";
            block->Push(dir);
        }
    }
}

void Player::OnCollisionStay(Collider* _self, Collider* _other)
{
    Entity* other = _other->GetOwner();
    if (!other) return;
    TagComponent* tag = other->GetComponent<TagComponent>();
    if (!tag) return;

    TransformComponent* transf = mOwner->GetComponent<TransformComponent>();
    CollisionSide side = _other->GetSide();

    if (tag->Is("Wall"))
    {
        Vector2f pos = transf->GetPos();
        if (side == CollisionSide::Top)    pos.y -= 2.f;
        if (side == CollisionSide::Bottom) pos.y += 2.f;
        if (side == CollisionSide::Left)   pos.x -= 2.f;
        if (side == CollisionSide::Right)  pos.x += 2.f;
        transf->SetPos(pos);
    }

    if (tag->Is("Gate"))
    {
        Vector2f pos = transf->GetPos();
        if (side == CollisionSide::Top)    pos.y -= 2.f;
        if (side == CollisionSide::Bottom) pos.y += 2.f;
        if (side == CollisionSide::Left)   pos.x -= 2.f;
        if (side == CollisionSide::Right)  pos.x += 2.f;
        transf->SetPos(pos);
    }

    if (tag->Is("Block"))
    {
        Vector2f pos = transf->GetPos();
        if (side == CollisionSide::Top)    pos.y -= 2.f;
        if (side == CollisionSide::Bottom) pos.y += 2.f;
        if (side == CollisionSide::Left)   pos.x -= 2.f;
        if (side == CollisionSide::Right)  pos.x += 2.f;
        transf->SetPos(pos);
    }

    if (tag->Is("Exit"))
    {
        std::cout << "[Player] Sortie atteinte !\n";
        if (m_onExitReached)
            m_onExitReached();
    }
}