#pragma once
#include "BaseEntity.hpp"

class BaseWeapon : public BaseEntity
{
private:
    unsigned int currentAmmo;
    unsigned int reserveAmmo;
public:
    virtual void draw(sf::RenderTarget& renderTarget) = 0;
    virtual void update(float f_delta) = 0;
};