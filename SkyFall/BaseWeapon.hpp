#pragma once
#include "BaseEntity.hpp"

#include "BulletProjectile.hpp"

#include <memory>

class BaseWeapon : public BaseObject
{
protected:
    const float reloadTime;
    const float fireRate;
    const unsigned magazineSize;
    const bool infiniteReserve = false;
protected:
    bool reloading;
    int currentAmmo;
    int reserveAmmo;
protected:
    BaseWeapon(const float reloadTime,
        const float fireRate,
        const unsigned magazineSize,
        const bool infiniteReserve);
public:
    BaseWeapon() = default;
public:
    virtual void updatePosition(sf::Vector2f& position) = 0;
    virtual void fire() = 0;
    virtual void reload() = 0;
};