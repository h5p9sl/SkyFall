#pragma once

#include "object.hpp"

#include <vector>
#include <SFML/Graphics.hpp>

class BaseScene : public BaseObject
{
protected:
    // The color used to clear the OpenGL buffer
    sf::Color m_backgroundColor;
public:
    std::vector<BaseObject*> m_sceneObjects;
public:
    BaseScene(const sf::Color& t_backgroundColor) : 
        m_backgroundColor(t_backgroundColor)
    {}
    BaseScene() = default;
    sf::Color __inline getBackgroundColor() { return this->m_backgroundColor; }
};