#pragma once

#include <SFML/Graphics.hpp>

#include "BaseObject.hpp"

class BulletProjectile : public BaseObject
{
protected:
    bool m_shouldDelete;
protected:
    float m_timeCreated;
    sf::RectangleShape m_sprite;
    sf::Vector2f m_velocity;
public:
    bool shouldDelete();
public:
    BulletProjectile(const sf::Vector2f& src, float direction, float velocity);
public:
    virtual void draw(sf::RenderTarget& renderTarget) override;
    virtual void update(float f_delta) override;
};