#pragma once
#include "Scene.h"
#include "Maze.h"
#include "PushBlock.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <set>
#include <map>  

class Find_the_way_out_scene : public Scene, public IBlockCallback
{
    Entity* m_player = nullptr;
    Maze    m_maze;

    sf::RenderTexture m_fogTexture;
    float m_DefogRadius = 0.f;

    sf::Text m_hudText;

    sf::Keyboard::Key m_ResetKey;
    bool mResetPressed;

    int m_currentLevel = 1;

    std::set<std::pair<int, int>> m_targetPositions;

    std::set<std::pair<int, int>> m_blocksOnTarget;

    std::vector<Entity*> m_gateEntities;

    std::vector<PushBlock*> m_pushBlocks;

    std::map<std::pair<int, int>, Entity*> m_holeEntities;

    void DrawMaze(sf::RenderWindow* _window);
    void SpawnWalls();
    void SetFog();
    void GoToNextLevel();
    void SpawnBullet(Vector2f pos, Vector2f direction);

public:
    Find_the_way_out_scene(int level = 1) : m_currentLevel(level) {}

    void OnBlockOnTarget(int targetRow, int targetCol) override;

    void OnDraw(sf::RenderWindow* _window) override;
    void OnUpdate() override;
    void OnEnter() override;
    void OnExit() override;
    void Create(const std::string& entity, float _posX, float _posY, int _width, int _height, float _rot) override;
};