#pragma once
#include "BaseEntity.hpp"
#include "BaseWeapon.hpp"
#include <vector>

class LocalPlayer : public BaseEntity
{
private:
    std::vector<BaseWeapon*> weapons;
public:
    virtual void draw(sf::RenderTarget& renderTarget);
    virtual void update(float f_delta);
};
