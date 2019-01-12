#include <iostream>
#include <string>
#include "LocalPlayer.hpp"

#include "Pistol.hpp"

#include "SkyFall.hpp"

using namespace SkyFall;

LocalPlayer::LocalPlayer() :
    placeHolder({ 18.f * 4, 31.f * 4 })
{
    placeHolder.setTexture(&globals->SPPlayer);
    
    // Set origin
    sf::FloatRect bottomCenter = this->placeHolder.getLocalBounds();
    bottomCenter.left += bottomCenter.width / 2.f;
    bottomCenter.top += bottomCenter.height;
    placeHolder.setOrigin(bottomCenter.left, bottomCenter.top);

    this->weapons.push_back(new WeaponPistol());
    this->currentWeapon = weapons.at(0);
}

LocalPlayer::~LocalPlayer()
{
}

void LocalPlayer::draw(sf::RenderTarget & renderTarget)
{
    renderTarget.draw(this->placeHolder);
    this->currentWeapon->draw(renderTarget);
}

void LocalPlayer::update(float f_delta)
{
    this->m_movement = { 0.f, 0.f };

    // Update movement vector
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && this->m_onGround) {
        this->m_movement.y = -1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        // Crouch
        this->m_animState = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        this->m_movement.x = -1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        this->m_movement.x = 1.f;
    }

    // Shooting
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        this->currentWeapon->reload();
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        this->currentWeapon->fire();
    }

    // Switch weapons
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
        this->currentWeapon = this->weapons.at(0);
    }

    // Get vector between mouse and position
    sf::Vector2i mousePosition = sf::Mouse::getPosition(globals->baseGame->mainWindow);
    sf::Vector2f mouseVector = { (float)mousePosition.x - this->m_position.x, (float)mousePosition.y - this->m_position.y };
    if (mouseVector.x < 0.f) {
        this->placeHolder.setScale({ -1.f, 1.f });
        this->m_isFlipped = true;
    }
    else {
        this->placeHolder.setScale({ 1.f, 1.f });
        this->m_isFlipped = false;
    }

    this->currentWeapon->update(f_delta);
    this->updatePhysics(f_delta);
    this->updateAnimation();
}

void LocalPlayer::updatePhysics(float f_delta)
{
    // Update horizontal velocity
    this->m_velocity.x += this->m_movement.x * 50.f;
    // Update vertical velocity
    this->m_velocity.y += this->m_movement.y * 650.f;
    // Apply gravity
    this->m_velocity.y += Constants::globalGravity;
    // Update position member
    this->m_position += this->m_velocity * f_delta;
    
    // Cap horizontal velocity
    {
        float horizontalVelocity = abs(m_velocity.x);
        if (horizontalVelocity > 800.f) {
            m_velocity.x /= horizontalVelocity;
        }
    }
    
    // TODO: Remove this once implimented global physics
    if (this->m_position.y >= globals->baseGame->mainWindow.getView().getSize().y)
    {
        this->m_position.y = 600.f;
        this->m_onGround = true;
        this->m_velocity.y = 0;
    }
    else {
        this->m_onGround = false;
    }
    
        
    // Decay horizontal velocity 
    this->m_velocity.x *= 0.9f;
    // Update collider
    this->placeHolder.setPosition(m_position);
}

void LocalPlayer::updateAnimation()
{

    switch (this->m_animState)
    {
    case 0:
        // Normal
        break;
    case 1:
        // Crouch
        break;
    }

    sf::Vector2f armPosition = this->m_position;
    if (this->m_isFlipped) {
        armPosition.y -= 18.f * 4;
        armPosition.x += 1.5f * 4;
    }
    else {
        armPosition.y -= 18.f * 4;
        armPosition.x -= 1.5f * 4;
    }
    this->currentWeapon->updatePosition(armPosition);
}
