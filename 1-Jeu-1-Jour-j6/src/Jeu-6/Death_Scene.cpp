#include "Death_Scene.h"
#include "GameManager.h"
#include "InputManager.h"
#include "SceneManager.h"

void Death_Scene::OnEnter()
{
    sf::Font& font = GameManager::Get()->GetFont();

    m_winText.setFont(font);
    m_winText.setString("Game Over !");
    m_winText.setCharacterSize(80);
    m_winText.setFillColor(sf::Color::Red);

    sf::FloatRect bounds = m_winText.getLocalBounds();
    m_winText.setOrigin(bounds.width * 0.5f, bounds.height * 0.5f);
    m_winText.setPosition(960.f, 440.f);

    m_subText.setFont(font);
    m_subText.setString("Vous ete  mort (Get better) !\n      Appuyez sur R pour rejouer");
    m_subText.setCharacterSize(35);
    m_subText.setFillColor(sf::Color::White);

    sf::FloatRect bounds2 = m_subText.getLocalBounds();
    m_subText.setOrigin(bounds2.width * 0.5f, bounds2.height * 0.5f);
    m_subText.setPosition(960.f, 580.f);
}


void Death_Scene::OnUpdate()
{
    InputManager* input = InputManager::Get();
    if (input->IsKeyDown(sf::Keyboard::R))
        SceneManager::Get()->ChangeScene("Level1");
}

void Death_Scene::OnDraw(sf::RenderWindow* _window)
{
    _window->draw(m_winText);
    _window->draw(m_subText);
}




