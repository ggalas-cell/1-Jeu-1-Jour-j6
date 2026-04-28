#pragma once
#include "Scene.h"
#include <SFML/Graphics.hpp>

class Win_Scene : public Scene
{
    sf::Text m_winText;
    sf::Text m_subText;

public:
    void OnDraw(sf::RenderWindow* _window) override;
    void OnUpdate() override;
    void OnEnter() override;
    void OnExit() override {}
    void Create(const std::string& entity, float _posX, float _posY, int _width, int _height, float _rot) override {}
};