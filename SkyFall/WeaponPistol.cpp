#include "WeaponPistol.hpp"

#include "SkyFall.hpp"

#include <iostream>

using namespace SkyFall;

WeaponPistol::WeaponPistol() :
    BaseWeapon(1.f, 0.3f, 18, true),
    m_sprite({16.f * 4, 5.f * 4})
{
    this->m_sprite.setTexture(&globals->SPPistol);
    this->m_sprite.setOrigin(1.5f * 4, 3.5f * 4);
}

WeaponPistol::~WeaponPistol()
{
}

void WeaponPistol::draw(sf::RenderTarget & renderTarget)
{
    renderTarget.draw(this->m_sprite);
}

void WeaponPistol::update(float f_delta)
{
    // Get vector between mouse and position
    sf::Vector2i mousePosition = sf::Mouse::getPosition(globals->baseGame->mainWindow);
    sf::Vector2f mouseVector = { (float)mousePosition.x - this->m_sprite.getPosition().x, (float)mousePosition.y - this->m_sprite.getPosition().y };
    float angle = atan2f(mouseVector.y, mouseVector.x) * 180.f / Constants::PI;

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
            globals->baseGame->gameObjectManager.addEntity(new BulletProjectile(
                this->m_sprite.getPosition(),
                this->m_sprite.getRotation() + 180.f,
                7000.f));
        }
        else
        {
            globals->baseGame->gameObjectManager.addEntity(new BulletProjectile(
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
