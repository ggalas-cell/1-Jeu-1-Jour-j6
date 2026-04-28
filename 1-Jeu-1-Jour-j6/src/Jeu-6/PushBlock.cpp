#include "PushBlock.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "TagComponent.h"
#include "Collider.h"
#include "Rigidbody2D.h"
#include "Maze.h"
#include <cmath>
#include <iostream>

PushBlock::PushBlock()
{
    m_isMoving = false;
}

void PushBlock::FixedUpdate()
{
    if (!m_isMoving) return;

    TransformComponent* transf = mOwner->GetComponent<TransformComponent>();
    Vector2f pos = transf->GetPos();

    float dx = m_targetPos.x - pos.x;
    float dy = m_targetPos.y - pos.y;
    float dist = std::sqrt(dx * dx + dy * dy);

    if (dist <= 3.f)
    {
        transf->SetPos(m_targetPos.x, m_targetPos.y);

        Rigidbody2D* rb = mOwner->GetComponent<Rigidbody2D>();
        if (rb) rb->SetVelocity(Vector2f(0.f, 0.f));

        m_isMoving = false;
        SnapToGrid();
        CheckTarget();
    }
    else
    {
        float step = m_moveSpeed * (1.f / 240.f);
        pos.x += m_moveDir.x * step;
        pos.y += m_moveDir.y * step;
        transf->SetPos(pos);
    }
}

void PushBlock::Push(Vector2f direction)
{
    if (m_isMoving || !m_maze) return;

    if (direction.x == 0.f && direction.y == 0.f) return;

    int dRow = 0, dCol = 0;
    if (std::abs(direction.x) >= std::abs(direction.y))
        dCol = (direction.x > 0.f) ? 1 : -1;
    else
        dRow = (direction.y > 0.f) ? 1 : -1;

    int newRow = m_gridRow + dRow;
    int newCol = m_gridCol + dCol;

    if (!CanMoveTo(newRow, newCol))
    {
        //std::cout << "[PushBlock] Mouvement bloque vers (" << newRow << "," << newCol << ") = '"
            //<< m_maze->GetCell(newRow, newCol) << "'\n";
        return;
    }

    m_maze->SetCell(m_gridRow, m_gridCol, ' ');

    m_moveDir.x = (float)dCol;
    m_moveDir.y = (float)dRow;

    float tx, ty;
    m_maze->GetWorldPos(newRow, newCol, tx, ty);
    m_targetPos.x = tx;
    m_targetPos.y = ty;

    m_gridRow = newRow;
    m_gridCol = newCol;
    m_isMoving = true;

    //std::cout << "[PushBlock] Pousse vers (" << newRow << "," << newCol << ")\n";
}

bool PushBlock::CanMoveTo(int row, int col)
{
    if (!m_maze) return false;
    if (row < 0 || row >= m_maze->GetRows()) return false;
    if (col < 0 || col >= m_maze->GetCols()) return false;

    char c = m_maze->GetCell(row, col);
    return (c == ' ' || c == 'T' || c == 'S');
}

void PushBlock::SnapToGrid()
{
    if (!m_maze) return;
    char current = m_maze->GetCell(m_gridRow, m_gridCol);
    if (current == 'T')
        m_maze->SetCell(m_gridRow, m_gridCol, 'O');
    else
        m_maze->SetCell(m_gridRow, m_gridCol, 'B');
}

void PushBlock::CheckTarget()
{
    if (!m_maze || !m_callback) return;
    char current = m_maze->GetCell(m_gridRow, m_gridCol);
    //std::cout << "[CheckTarget] cell='" << current << "' at (" << m_gridRow << "," << m_gridCol << ")\n";
    if (current == 'O')
        m_callback->OnBlockOnTarget(m_gridRow, m_gridCol);
}

void PushBlock::OnCollisionStay(Collider* _self, Collider* _other)
{
    Entity* other = _other->GetOwner();
    if (!other) return;
    TagComponent* tag = other->GetComponent<TagComponent>();
    if (!tag) return;
    TransformComponent* transf = mOwner->GetComponent<TransformComponent>();
    CollisionSide side = _other->GetSide();

    if (tag->Is("Wall") || tag->Is("Gate"))
    {
        if (m_isMoving)
        {
            m_isMoving = false;
            Rigidbody2D* rb = mOwner->GetComponent<Rigidbody2D>();
            if (rb) rb->SetVelocity(Vector2f(0.f, 0.f));

            m_gridRow -= (int)m_moveDir.y;
            m_gridCol -= (int)m_moveDir.x;

            float tx, ty;
            m_maze->GetWorldPos(m_gridRow, m_gridCol, tx, ty);
            transf->SetPos(tx, ty);
            m_maze->SetCell(m_gridRow, m_gridCol, 'B');
        }

        Vector2f pos = transf->GetPos();
        if (side == CollisionSide::Top)    pos.y -= 2.f;
        if (side == CollisionSide::Bottom) pos.y += 2.f;
        if (side == CollisionSide::Left)   pos.x -= 2.f;
        if (side == CollisionSide::Right)  pos.x += 2.f;
        transf->SetPos(pos);
    }
}