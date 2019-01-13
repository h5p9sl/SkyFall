#pragma once

#include <SFML/Graphics.hpp>

#include "BaseObject.hpp"

class BulletProjectile : public BaseObject
{
public:
    bool shouldDelete;
protected:
    float timeCreated;
    sf::RectangleShape sprite;
    sf::Vector2f direction;
    float velocity;
public:
    BulletProjectile(const sf::Vector2f& src, float direction, float velocity);
public:
    virtual void draw(sf::RenderTarget& renderTarget) override;
    virtual void update(float f_delta) override;
};