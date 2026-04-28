#pragma once
#include "Component.h"
#include "Updatable.h"
#include "Vector2f.h"

class TransformComponent;

class Camera : public Component, public Updatable
{
private:
    TransformComponent* m_target = nullptr;  // who to follow
    float               m_lerpSpeed = 5.f;
    sf::View view;
    float mCurrentZoom;
    // World bounds clamp 
    // 0 = no bounds, may change when level size is decided
    float m_worldMinX = 0.f;
    float m_worldMaxX = 0.f;
    float m_worldMinY = 0.f;
    float m_worldMaxY = 0.f;

    Vector2f m_currentPos;
    
public:
    Camera(float _worldMaxX, float _worldMaxY);
    ~Camera();
    void SetTarget(TransformComponent* _target) { m_target = _target; }

    void SetLerpSpeed(float _s) { m_lerpSpeed = _s; }

    // Clamp the camera  /never shows outside the level bounds
    void SetWorldBounds(float minX, float maxX, float minY, float maxY)
    {
        m_worldMinX = minX; m_worldMaxX = maxX;
        m_worldMinY = minY; m_worldMaxY = maxY;
    }

    void Update() override;

private:
    // Lerp helper : for smooth camera movement
    static float Lerp(float a, float b, float t) { return a + (b - a) * t; }
};

