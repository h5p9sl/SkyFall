#pragma once
#include "base/entity.hpp"

class SpriteSheet;

class Enemy : public BaseEntity
{
private:
    SpriteSheet* m_spriteSheet;
    sf::RectangleShape m_sprite;
    sf::Vector2f m_velocity;
public:
    Enemy();
    ~Enemy();
public:
    virtual void draw(sf::RenderTarget& renderTarget) override;
    virtual void update(float f_delta) override;
private:
    virtual void updatePhysics(float f_delta);
};

