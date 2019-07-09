#include "Scene1.hpp"

#include "SkyFall.hpp"

SkyFall::Scenes::Scene1::Scene1() :
    m_background({ (float)globals->baseGame->mainWindow.getSize().x, (float)globals->baseGame->mainWindow.getSize().y }),
    BaseScene(sf::Color(0x66242a00))
{
    globals->musicBackground01.play();

    this->m_background.setTexture(&globals->SPScene1Background);
    this->m_background.setScale(2.f, 2.f);
    this->m_background.setPosition({ -200.f, -500.f });
}

void SkyFall::Scenes::Scene1::draw(sf::RenderTarget & renderTarget)
{
    renderTarget.draw(this->m_background);

    for (auto object : this->m_sceneObjects) {
        object->draw(renderTarget);
    }
}

void SkyFall::Scenes::Scene1::update(float f_delta)
{
    for (auto object : this->m_sceneObjects) {
        object->update(f_delta);
    }
}
