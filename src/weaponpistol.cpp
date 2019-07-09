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
    m_spriteSheet(&globals->SPPistol),
    m_animState(0)
{
    // Initialize m_sprite size
    this->m_sprite.setSize(
        sf::Vector2f(
            this->m_spriteSheet->m_spriteSize.x * 4.f,
            this->m_spriteSheet->m_spriteSize.y * 4.f
        )
    );
    this->m_sprite.setOrigin(1.5f * 4.f, 7.5f * 4.f);
    this->m_sprite.setTexture(this->m_spriteSheet);
    this->projectiles.reserve(static_cast<int>(1.f / flt_fireRate) + 1);
}

WeaponPistol::~WeaponPistol()
{
}

void WeaponPistol::updateAnimation() {
    static float t = 0.f;

    switch (this->m_animState) {
    case 0:
        this->m_sprite.setTextureRect(this->m_spriteSheet->getSpriteAt(0, 0));
        break;
    case 1:
        // The player just shot a bullet.
        this->m_sprite.setTextureRect(this->m_spriteSheet->getSpriteAt(1, 0));
        if (t == 0.f) t = globals->currentTime;
        if (globals->currentTime - t > 0.1f) {
            t = 0.f;
            this->m_animState = 2;
        }
        break;
    case 2:
        this->m_sprite.setTextureRect(this->m_spriteSheet->getSpriteAt(2, 0));
        if (t == 0.f) t = globals->currentTime;
        if (globals->currentTime - t > 0.1f) {
            t = 0.f;
            this->m_animState = 0;
        }
        break;
    }
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

    this->updateAnimation();
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
        // Start shooting animation
        this->m_animState = 1;

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
