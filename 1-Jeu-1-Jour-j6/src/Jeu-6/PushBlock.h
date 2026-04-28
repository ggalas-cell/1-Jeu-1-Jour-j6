#pragma once
#include "Component.h"
#include "Collidable.h"
#include "FixedUpdatable.h"
#include "Vector2f.h"

class IBlockCallback
{
public:
    virtual void OnBlockOnTarget(int targetRow, int targetCol) = 0;
    virtual ~IBlockCallback() = default;
};



class PushBlock : public Component, public Collidable, public FixedUpdatable
{
public:
    class Maze* m_maze = nullptr;
    IBlockCallback* m_callback = nullptr;

    int m_gridRow = 0;
    int m_gridCol = 0;

    bool m_isMoving = false;
    Vector2f m_targetPos;
    Vector2f m_moveDir;

    float m_moveSpeed = 300.f;

    PushBlock();

    void FixedUpdate() override;

    void Push(Vector2f direction);

    void OnCollisionEnter(Collider* _self, Collider* _other) override {}
    void OnCollisionStay(Collider* _self, Collider* _other) override;
    void OnCollisionExit(Collider* _self, Collider* _other) override {}

private:
    bool CanMoveTo(int row, int col);
    void SnapToGrid();
    void CheckTarget();
};