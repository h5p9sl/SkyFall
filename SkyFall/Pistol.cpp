#include "Pistol.hpp"

#include "SkyFall.hpp"

#include <iostream>

using namespace SkyFall;

WeaponPistol::WeaponPistol() :
    BaseWeapon(0.5f, 18, true),
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
    float hypotenuse = sqrtf(mouseVector.x * mouseVector.x + mouseVector.y * mouseVector.y);
    float angle = atan2f(mouseVector.y, mouseVector.x) * 180.f / Constants::PI;

    if (mouseVector.x < 0.f) {
        this->m_sprite.setScale(-1.f, 1.f);
        angle += 180.f;
    }
    else {
        this->m_sprite.setScale(1.f, 1.f);
    }

    this->m_sprite.setRotation(angle);

    static bool lastReloadingState = false;
    if (this->reloading) {
        static float timeStamp = 0.f;
        if (!lastReloadingState) {
            timeStamp = globals->currentTime + this->reloadTime;
        }
        if (globals->currentTime >= timeStamp) {
            this->reloading = false;
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
    if (!this->reloading) {
        std::cout << "Pew!" << std::endl;
    }
}

void WeaponPistol::reload()
{
    if (!this->reloading &&
        this->currentAmmo < this->magazineSize)
    {
        this->reloading = true;
        std::cout << "Reloading..." << std::endl;
    }
}
