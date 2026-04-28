#include "Camera.h"
#include "TransformComponent.h"
#include "Entity.h"
#include "GameManager.h"
#include <algorithm>
#include <iostream>
#include "InputManager.h"

Camera::Camera(float _worldMaxX, float _worldMaxY) {
    SetLerpSpeed(6.f);
    SetWorldBounds(0.f, _worldMaxX, 0.f, _worldMaxY);
    sf::RenderWindow* window = GameManager::Get()->GetWindow();
    if (!window) return;
    mCurrentZoom = 1;
    view = window->getView();
    view.zoom(0.5);
}

Camera::~Camera()
{
    sf::RenderWindow* window = GameManager::Get()->GetWindow();
    window->setView(window->getDefaultView());
}

void Camera::Update()
{
    if (m_target == nullptr) {
        SetTarget(mOwner->GetComponent<TransformComponent>());
    }

    InputManager* im = InputManager::Get();
    if (im->IsWheelUp()) {
        if (mCurrentZoom >= 0.7) {
            mCurrentZoom *= (1 - 0.1f);
            view.zoom(1 - 0.1f);
        }
       
    }
    else if (im->IsWheelDown()) {
        if (mCurrentZoom <= 1.9) {
            mCurrentZoom *= (1 + 0.1f);
            view.zoom(1 + 0.1f);
            view.zoom(1 + 0.1f);
        }

    }


    if (!m_target) return;

    sf::RenderWindow* window = GameManager::Get()->GetWindow();
    if (!window) return;

    float dt = mOwner->GetDeltaTime();
    Vector2f targetPos = m_target->GetPos();



    float t = 1.f - std::pow(1.f - std::min(m_lerpSpeed * (1.f / mCurrentZoom) * dt, 1.f), 1.f);
    m_currentPos.x = Lerp(m_currentPos.x, targetPos.x, t);
    m_currentPos.y = Lerp(m_currentPos.y, targetPos.y, t);

    float halfW = view.getSize().x * 0.5f;
    float halfH = view.getSize().y * 0.5f;

    float camX = m_currentPos.x;
    float camY = m_currentPos.y;

    if (m_worldMaxX > m_worldMinX)
    {
        camX = std::max(camX, m_worldMinX + halfW);
        camX = std::min(camX, m_worldMaxX - halfW);
        camY = std::max(camY, m_worldMinY + halfH);
        camY = std::min(camY, m_worldMaxY - halfH);
    }
    view.setCenter(camX, camY);
    window->setView(view);
}