#include <iostream>
#include "GameManager.h"
#include "SceneManager.h"
#include "Find_the_way_out_scene.h"
#include "Win_Scene.h"
#include "main.h"
#include <SFML/Graphics.hpp>

int main()
{
    GameManager* game = GameManager::Get();
    SceneManager* sm = SceneManager::Get();

    game->Init("Level1", 1920, 1080, 60);

    sm->AddScene("Level1", new Find_the_way_out_scene(1));
    sm->AddScene("Level2", new Find_the_way_out_scene(2));
    sm->AddScene("Level3", new Find_the_way_out_scene(3));
    sm->AddScene("Win_Scene", new Win_Scene());

    sm->SetStartScene("Level1");
    game->Run();

    return 0;
}