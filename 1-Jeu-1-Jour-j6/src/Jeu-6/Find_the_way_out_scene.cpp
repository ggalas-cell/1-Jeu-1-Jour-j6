#include "Find_the_way_out_scene.h"
#include "Player.h"
#include "PushBlock.h"
#include <TagComponent.h>
#include <TransformComponent.h>
#include <Rigidbody2D.h>
#include <BoxCollider.h>
#include "CollisionLayer.h"
#include "SceneManager.h"
#include <iostream>
#include <InputManager.h>
#include "GameManager.h"


void Find_the_way_out_scene::DrawMaze(sf::RenderWindow* _window)
{
    int cs = m_maze.mCellSize;
    sf::RectangleShape cell(sf::Vector2f((float)cs, (float)cs));

    for (int row = 0; row < m_maze.GetRows(); row++)
    {
        for (int col = 0; col < m_maze.GetCols(); col++)
        {
            char c = m_maze.GetCell(row, col);
            switch (c)
            {
            case '#': cell.setFillColor(sf::Color(40, 40, 50));  break; // mur
            case 'G': cell.setFillColor(sf::Color(180, 60, 60));  break; // gate
            case 'E': cell.setFillColor(sf::Color(50, 200, 100)); break; // sortie
            case 'B': cell.setFillColor(sf::Color(180, 130, 60));  break; // bloc
            case 'O': cell.setFillColor(sf::Color(140, 60, 180)); break; // bloc sur target
            case 'T': cell.setFillColor(sf::Color(80, 80, 200)); break; // target
            case 'S': cell.setFillColor(sf::Color(200, 200, 100)); break; // spawn
            default:  cell.setFillColor(sf::Color(210, 210, 210)); break; // couloir
            }
            cell.setPosition((float)(col * cs), (float)(row * cs));
            _window->draw(cell);
        }
    }
}


void Find_the_way_out_scene::SpawnWalls()
{
    m_targetPositions.clear();
    m_blocksOnTarget.clear();
    m_gateEntities.clear();
    m_pushBlocks.clear();

    int cs = m_maze.mCellSize;

    for (int row = 0; row < m_maze.GetRows(); row++)
    {
        for (int col = 0; col < m_maze.GetCols(); col++)
        {
            char c = m_maze.GetCell(row, col);
            float x = col * cs + cs * 0.5f;
            float y = row * cs + cs * 0.5f;

            if (c == '#')
            {
                bool isBorder = false;
                int dr[] = { -1, 1, 0, 0 };
                int dc[] = { 0, 0, -1, 1 };
                for (int d = 0; d < 4; d++)
                {
                    int nr = row + dr[d];
                    int nc = col + dc[d];
                    if (nr >= 0 && nr < m_maze.GetRows() &&
                        nc >= 0 && nc < m_maze.GetCols())
                    {
                        char neighbor = m_maze.GetCell(nr, nc);
                        if (neighbor != '#')
                        {
                            isBorder = true;
                            break;
                        }
                    }
                }
                if (!isBorder) continue;
                Entity* wall = CreateEntity();
                wall->AddComponent<TagComponent>("Wall");
                wall->GetComponent<TransformComponent>()->SetPos(x, y);
                wall->AddComponent<BoxCollider>((float)cs, (float)cs, ENV_LAYER, PLAYER_LAYER | BLOCK_LAYER);
            }
            else if (c == 'G')
            {
                Entity* gate = CreateEntity();
                gate->AddComponent<TagComponent>("Gate");
                gate->GetComponent<TransformComponent>()->SetPos(x, y);
                gate->AddComponent<BoxCollider>((float)cs, (float)cs, ENV_LAYER, PLAYER_LAYER | BLOCK_LAYER);
                m_gateEntities.push_back(gate);
            }
            else if (c == 'E')
            {
                Entity* exit = CreateEntity();
                exit->AddComponent<TagComponent>("Exit");
                exit->GetComponent<TransformComponent>()->SetPos(x, y);
                BoxCollider* col2 = exit->AddComponent<BoxCollider>((float)cs, (float)cs, ENV_LAYER, PLAYER_LAYER);
                col2->SetTrigger(true);
            }
            else if (c == 'T')
            {
                m_targetPositions.insert({ row, col });

                Entity* hole = CreateEntity();
                hole->AddComponent<TagComponent>("Hole");
                hole->GetComponent<TransformComponent>()->SetPos(x, y);
                BoxCollider* hbc = hole->AddComponent<BoxCollider>((float)cs, (float)cs, TARGET_LAYER, BLOCK_LAYER);
                m_holeEntities[{row, col}] = hole;
            }
            else if (c == 'B')
            {
                Entity* blockEntity = CreateEntity();
                blockEntity->AddComponent<TagComponent>("Block");
                blockEntity->GetComponent<TransformComponent>()->SetPos(x, y);
                BoxCollider* bc = blockEntity->AddComponent<BoxCollider>((float)(cs - 4), (float)(cs - 4), BLOCK_LAYER, ENV_LAYER | PLAYER_LAYER| TARGET_LAYER);
                bc->SetVisible(true);
                bc->SetTrigger(false);

                PushBlock* pb = blockEntity->AddComponent<PushBlock>();
                pb->m_maze = &m_maze;
                pb->m_callback = this;
                pb->m_gridRow = row;
                pb->m_gridCol = col;
                m_pushBlocks.push_back(pb);
            }
        }
    }
}


void Find_the_way_out_scene::SetFog()
{
    m_fogTexture.clear(sf::Color::Black);

    sf::CircleShape vision(m_DefogRadius);
    Vector2f playerPos = m_player->GetComponent<TransformComponent>()->GetPos();

    vision.setFillColor(sf::Color::White);
    vision.setOrigin(m_DefogRadius, m_DefogRadius);
    vision.setPosition(playerPos);
    m_fogTexture.draw(vision);
    m_fogTexture.display();
}

void Find_the_way_out_scene::OnBlockOnTarget(int targetRow, int targetCol)
{
    auto key = std::make_pair(targetRow, targetCol);

    if (m_targetPositions.count(key))
    {
        m_blocksOnTarget.insert(key);
        //std::cout << "[Scene] Bloc sur target (" << targetRow << "," << targetCol
        //    << ") — " << m_blocksOnTarget.size() << "/" << m_targetPositions.size() << "\n";

        auto holeIt = m_holeEntities.find(key);
        if (holeIt != m_holeEntities.end())
        {
            DestroyEntity(holeIt->second);
            m_holeEntities.erase(holeIt);
        }

        if (m_blocksOnTarget.size() == m_targetPositions.size())
        {
            std::cout << "[Scene] Gates ouvertes !\n";
            for (Entity* gate : m_gateEntities)
            {
                TransformComponent* t = gate->GetComponent<TransformComponent>();
                Vector2f pos = t->GetPos();
                int gr, gc;
                m_maze.WorldToGrid(pos.x, pos.y, gr, gc);
                m_maze.SetCell(gr, gc, ' ');

                DestroyEntity(gate);
            }
            m_gateEntities.clear();
        }
    }
    else
    {
        m_blocksOnTarget.erase(key);
    }
}


void Find_the_way_out_scene::GoToNextLevel()
{
    int nextLevel = m_currentLevel + 1;
    if (nextLevel > 3)
    {
        SceneManager::Get()->ChangeScene("Win_Scene");
        return;
    }
    std::string sceneName = "Level" + std::to_string(nextLevel);
    std::cout << "[Scene] Passage au " << sceneName << "\n";
    SceneManager::Get()->ChangeScene(sceneName);

}




void Find_the_way_out_scene::OnEnter()
{
    if (m_currentLevel == 1) m_DefogRadius = 0.f;
    else if (m_currentLevel == 2) m_DefogRadius = 250.f;
    else                          m_DefogRadius = 150.f;

    m_maze.LoadLevel(m_currentLevel);
    m_fogTexture.create(1920, 1080);

    SpawnWalls();

    float spawnX = 90.f, spawnY = 90.f;
    for (int row = 0; row < m_maze.GetRows(); row++)
        for (int col = 0; col < m_maze.GetCols(); col++)
            if (m_maze.GetCell(row, col) == 'S')
                m_maze.GetWorldPos(row, col, spawnX, spawnY);
    
    m_ResetKey = sf::Keyboard::Key::E;
    mResetPressed = false;

    Create("Player", spawnX, spawnY, 0, 0, 0);

    if (m_currentLevel == 1)
    {
        sf::Font& font = GameManager::Get()->GetFont();
        m_hudText.setFont(font);
        m_hudText.setCharacterSize(22);
        m_hudText.setFillColor(sf::Color::White);
        m_hudText.setPosition(20.f, 950.f);
        m_hudText.setString(
            "ZQSD : Deplacer    R : Recommencer\n"
            "But : Pousser le bloc ORANGE sur le bloc BLEU pour ouvrir la porte ROUGE\n"
            "Rejoinds ensuite la sortie VERTE !   Spawn : JAUNE"
        );
    }

    if (m_currentLevel >= 2)
    {
        sf::Font& font = GameManager::Get()->GetFont();
        m_hudText.setFont(font);
        m_hudText.setCharacterSize(20);
        m_hudText.setFillColor(sf::Color::White);
        m_hudText.setPosition(1500.f, 400.f); // droite de l'écran
        m_hudText.setString(
            "ZQSD : Deplacer\n"
            "R : Recommencer\n\n"
            "But : Pousser les blocs\n"
            "ORANGES sur les blocs\n"
            "BLEUS pour ouvrir\n"
            "la porte ROUGE\n\n"
            "Rejoins la sortie VERTE !"
        );
    }
}

void Find_the_way_out_scene::OnUpdate()
{
    InputManager* input = InputManager::Get();
    mResetPressed = input->IsKeyHeld(m_ResetKey);
    if (mResetPressed)
    {
        SceneManager* sm = SceneManager::Get();
        sm->ReloadScene();
    }
}

void Find_the_way_out_scene::OnDraw(sf::RenderWindow* _window)
{
    DrawMaze(_window);
    if (m_currentLevel > 1) 
    {
        SetFog();
        sf::Sprite fogSprite(m_fogTexture.getTexture());
        _window->draw(fogSprite, sf::BlendMultiply);
        _window->draw(m_hudText);
    }
    if (m_currentLevel == 1)
        _window->draw(m_hudText);
   
}

void Find_the_way_out_scene::OnExit()
{
    m_player = nullptr;
    m_gateEntities.clear();
    m_pushBlocks.clear();
    m_targetPositions.clear();
    m_blocksOnTarget.clear();
}

void Find_the_way_out_scene::Create(const std::string& entity, float _posX, float _posY, int _width, int _height, float _rot)
{
    if (entity == "Player")
    {
        m_player = CreateEntity();
        m_player->AddComponent<TagComponent>("Player");
        m_player->GetComponent<TransformComponent>()->SetPos(_posX, _posY);
        m_player->GetComponent<TransformComponent>()->SetScale(1.f, 1.f);
        m_player->AddComponent<Rigidbody2D>(1.f, false, 0.f);

        BoxCollider* col = m_player->AddComponent<BoxCollider>(32.f, 32.f, PLAYER_LAYER, ENV_LAYER | BLOCK_LAYER);
        col->SetVisible(true);
        col->SetTrigger(true);

        Player* player = m_player->AddComponent<Player>();
        player->SetOnExitCallback([this]() {
            GoToNextLevel();
            });
    }
}
