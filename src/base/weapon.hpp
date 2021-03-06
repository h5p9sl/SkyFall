#pragma once
#include "entity.hpp"

#include "../bulletprojectile.hpp"

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
    std::vector<std::unique_ptr<BulletProjectile>> projectiles;
protected:
    BaseWeapon(const float reloadTime,
        const float fireRate,
        const unsigned magazineSize,
        const bool infiniteReserve);
public:
    BaseWeapon() = default;
    virtual ~BaseWeapon();
public:
    virtual void updatePosition(sf::Vector2f& position) = 0;
    virtual void fire() = 0;
    virtual void reload() = 0;
};

