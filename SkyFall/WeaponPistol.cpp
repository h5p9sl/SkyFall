#include "WeaponPistol.hpp"

#include "SkyFall.hpp"

#include <iostream>
#include <algorithm>
#include <memory>

using namespace SkyFall;

constexpr float flt_fireRate = 0.3f;
constexpr float flt_reloadTime = 1.f;
constexpr int int_magazineCapacity = 18;

WeaponPistol::WeaponPistol() :
    BaseWeapon(flt_reloadTime, flt_fireRate, int_magazineCapacity, true),
    m_sprite({16.f * 4, 5.f * 4})
{
    this->m_sprite.setTexture(&globals->SPPistol);
    this->m_sprite.setOrigin(1.5f * 4, 3.5f * 4);
    this->projectiles.reserve(static_cast<int>(1.f / flt_fireRate) + 1);
}

WeaponPistol::~WeaponPistol()
{
}

void WeaponPistol::draw(sf::RenderTarget & renderTarget)
{
    for (auto& bullet : this->projectiles) {
        bullet->draw(renderTarget);
    }

    renderTarget.draw(this->m_sprite);
}

void WeaponPistol::update(float f_delta)
{
    // Get vector between mouse and position
    // sf::Vector2i mousePosition = sf::Mouse::getPosition(globals->baseGame->mainWindow);
    sf::Vector2f mousePosition = globals->baseGame->mainWindow.getView().getCenter();
    sf::Vector2f mouseVector = { mousePosition.x - this->m_sprite.getPosition().x, mousePosition.y - this->m_sprite.getPosition().y };
    float angle = atan2f(mouseVector.y, mouseVector.x) * 180.f / Constants::PI;

    // Flip to face cursor
    if (mouseVector.x < 0.f) {
        this->m_sprite.setScale(-1.f, 1.f);
        this->m_isFlipped = true;
        angle += 180.f;
    }
    else {
        this->m_sprite.setScale(1.f, 1.f);
        this->m_isFlipped = false;
    }
    this->m_sprite.setRotation(angle);

    // Reloading logic
    static bool lastReloadingState = false;
    if (this->reloading)
    {
        static float timeStamp = 0.f;
        
        if (!lastReloadingState) {
            timeStamp = globals->currentTime + this->reloadTime;
        }

        if (globals->currentTime >= timeStamp) {
            this->reloading = false;
            if (!this->infiniteReserve) {
                int diff = this->magazineSize - this->currentAmmo;
                if (reserveAmmo - diff > 0) {
                    currentAmmo += diff;
                    reserveAmmo -= diff;
                }
                else {
                    currentAmmo += reserveAmmo;
                    reserveAmmo = 0;
                }
            }
            else {
                this->currentAmmo = this->magazineSize;
            }
        }
    }
    lastReloadingState = this->reloading;

    // Erase bullets that should be deleted
    this->projectiles.erase(
        std::remove_if(this->projectiles.begin(), this->projectiles.end(), [](std::unique_ptr<BulletProjectile>& bullet) {
            return bullet->shouldDelete();
        }),
        this->projectiles.end()
    );

    // Update all projectiles
    for (auto& bullet : this->projectiles) {
        bullet->update(f_delta);
    }
}

void WeaponPistol::updatePosition(sf::Vector2f& position)
{
    this->m_sprite.setPosition(position);
}

void WeaponPistol::fire()
{
    static float nextShot = 0.f;
    if (!this->reloading &&
        this->currentAmmo > 0 &&
        globals->currentTime >= nextShot)
    {
        nextShot = globals->currentTime + this->fireRate;
        this->currentAmmo--;

        if (this->m_isFlipped)
        {
            this->projectiles.push_back(std::make_unique<BulletProjectile>(
                this->m_sprite.getPosition(),
                this->m_sprite.getRotation() + 180.f,
                7000.f));
        }
        else
        {
            this->projectiles.push_back(std::make_unique<BulletProjectile>(
                this->m_sprite.getPosition(),
                this->m_sprite.getRotation(),
                7000.f));
        }
        std::cout << "Pew! " << this->currentAmmo << std::endl;
        
        globals->SFXPistolShoot1.play();

        // Automatically reload
        if (this->currentAmmo == 0) {
            this->reload();
        }
    }
}

void WeaponPistol::reload()
{
    if (!this->reloading &&
        this->currentAmmo < (int)this->magazineSize)
    {
        this->reloading = true;
        std::cout << "Reloading..." << std::endl;
    }
}
