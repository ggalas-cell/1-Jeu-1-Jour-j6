#pragma once
#include "Component.h"
#include "Updatable.h"
#include "FixedUpdatable.h"
#include "Collidable.h"
#include <SFML/Window.hpp>
#include "Vector2f.h"
#include <functional>

class Player : public Component, public Updatable, public FixedUpdatable, public Collidable
{
    float m_sqeed;

    bool mMovingLeft;
    bool mMovingRight;
    bool mMovingUp;
    bool mMovingDown;

    bool mShootingUp;
    bool mShootingDown;
    bool mShootingLeft;
    bool mShootingRight;
    bool mReloading;

    sf::Keyboard::Key m_moveLeftKey;
    sf::Keyboard::Key m_moveRightKey;
    sf::Keyboard::Key m_moveUpKey;
    sf::Keyboard::Key m_moveDownKey;

    sf::Keyboard::Key m_ShootUpKey;
    sf::Keyboard::Key m_ShootDownKey;
    sf::Keyboard::Key m_ShootLeftKey;
    sf::Keyboard::Key m_ShootRightKey;
    sf::Keyboard::Key m_ReloadKey;


    std::function<void()> m_onExitReached;

public:
    Player();

    void SetOnExitCallback(std::function<void()> callback) { m_onExitReached = callback; }

    Vector2f GetMoveDirection() const;

    void Update() override;
    void FixedUpdate() override;

    void OnCollisionEnter(Collider* _self, Collider* _other) override;
    void OnCollisionStay(Collider* _self, Collider* _other) override;
    void OnCollisionExit(Collider* _self, Collider* _other) override {}
};