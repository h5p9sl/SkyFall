#pragma once
#include <SFML/Graphics.hpp>
#include "BaseObject.hpp"

// Pure virtual class
class BaseEntity : public BaseObject
{
protected:
    unsigned int m_health;
    sf::Vector2f m_position;
    bool m_onGround;
public:
    auto __inline getHealth() { return this->m_health; }
    auto __inline getPosition() { return this->m_position; }
};
