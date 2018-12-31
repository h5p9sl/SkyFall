#pragma once
#include "BaseEntity.hpp"
#include "BaseWeapon.hpp"
#include <vector>

class LocalPlayer : public BaseEntity
{
private:
    sf::RectangleShape placeHolder;
    sf::Vector2f m_velocity;
private:
    std::vector<BaseWeapon*> weapons;
public:
    LocalPlayer();
    ~LocalPlayer();
public:
    virtual void draw(sf::RenderTarget& renderTarget);
    virtual void update(float f_delta);
};
