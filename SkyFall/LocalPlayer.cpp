#include <iostream>
#include <string>
#include "LocalPlayer.hpp"

#include "WeaponPistol.hpp"

#include "SkyFall.hpp"

using namespace SkyFall;

LocalPlayer::LocalPlayer() :
    m_sprite({ 20.f * 4, 32.f * 4 }),
    m_enablePlayerControls(true)
{
    m_sprite.setTexture(&globals->SPPlayer);
    m_sprite.setTextureRect({ 0, 0, 20, 32 });
    
    // Set origin
    sf::FloatRect bottomCenter = this->m_sprite.getLocalBounds();
    bottomCenter.left += bottomCenter.width / 2.f;
    bottomCenter.top += bottomCenter.height;
    m_sprite.setOrigin(bottomCenter.left, bottomCenter.top);

    this->weapons.push_back(new WeaponPistol());
    this->currentWeapon = this->weapons.at(0);
}

LocalPlayer::~LocalPlayer()
{
}

void LocalPlayer::draw(sf::RenderTarget & renderTarget)
{
    renderTarget.draw(this->m_sprite);
    if (this->currentWeapon != nullptr) this->currentWeapon->draw(renderTarget);
}

void LocalPlayer::update(float f_delta)
{
    this->m_movement = { 0.f, 0.f };

    if (this->m_enablePlayerControls) {

        // Update movement vector
        if (Input::wasKeyPressed(sf::Keyboard::W) && this->m_onGround) {
            this->m_movement.y = -1.f;
        }
        if (Input::isKeyPressed(sf::Keyboard::A)) {
            this->m_movement.x = -1.f;
        }
        if (Input::isKeyPressed(sf::Keyboard::D)) {
            this->m_movement.x = 1.f;
        }

        // Shooting
        if (Input::wasKeyPressed(sf::Keyboard::R) &&
            this->currentWeapon != nullptr)
        {
            this->currentWeapon->reload();
        }
        if (Input::isButtonPressed(sf::Mouse::Left)) {
            if (this->currentWeapon != nullptr) {
                this->currentWeapon->fire();
            }
        }

        // Switch weapons
        if (Input::wasKeyPressed(sf::Keyboard::Num1)) {
            if (this->currentWeapon == this->weapons.at(0)) {
                this->currentWeapon = nullptr;
            }
            else {
                this->currentWeapon = this->weapons.at(0);
            }
        }

        // Get vector between mouse and position
        sf::Vector2i mousePosition = sf::Mouse::getPosition(globals->baseGame->mainWindow);
        sf::Vector2f mouseVector = { (float)mousePosition.x - this->m_position.x, (float)mousePosition.y - this->m_position.y };
        if (mouseVector.x < 0.f) {
            this->m_sprite.setScale({ -1.f, 1.f });
            this->m_isFlipped = true;
        }
        else {
            this->m_sprite.setScale({ 1.f, 1.f });
            this->m_isFlipped = false;
        }

    }

    if (this->currentWeapon != nullptr) this->currentWeapon->update(f_delta);
    this->updatePhysics(f_delta);
    this->updateAnimation();
}

void LocalPlayer::updatePhysics(float f_delta)
{
    // Update horizontal velocity
    this->m_velocity.x += this->m_movement.x * 30.f;
    // Update vertical velocity
    this->m_velocity.y += this->m_movement.y * 550.f;
    // Apply gravity
    this->m_velocity.y += Constants::globalGravity;
    // Update position member
    this->m_position += this->m_velocity * f_delta;
    
    // Cap horizontal velocity
    {
        float horizontalVelocity = abs(m_velocity.x);
        if (horizontalVelocity > globals->baseGame->mainWindow.getView().getSize().x) {
            m_velocity.x /= horizontalVelocity;
        }
    }
    
    // TODO: Remove this once implimented global physics
    if (this->m_position.y >= globals->baseGame->mainWindow.getView().getSize().y)
    {
        this->m_position.y = globals->baseGame->mainWindow.getView().getSize().y;
        this->m_onGround = true;
        this->m_velocity.y = 0;
    }
    else {
        this->m_onGround = false;
    }
    
        
    // Decay horizontal velocity 
    this->m_velocity.x *= 0.9f;
    // Update collider
    this->m_sprite.setPosition(m_position);
}

void LocalPlayer::updateAnimation()
{
    sf::Vector2f armPosition = this->m_position;
    // Set arm position
    armPosition.y -= 18.f * 4;
    // Offset x position based on which direction player is facing
    (this->m_isFlipped) ? armPosition.x -= 1.5f * 4 : armPosition.x += 1.5f * 4;
    if (this->currentWeapon != nullptr) {
        this->currentWeapon->updatePosition(armPosition);
    }

    // Get vector between mouse and position
    sf::Vector2i mousePosition = sf::Mouse::getPosition(globals->baseGame->mainWindow);
    sf::Vector2f mouseVector = { (float)mousePosition.x - armPosition.x, (float)mousePosition.y - armPosition.y };
    float angle = atan2f(mouseVector.y, mouseVector.x) * 180.f / Constants::PI;
    // Variable to store coordinates for spritesheet
    sf::Vector2i textureCoords;

    // TODO: fix this spaghetti code
    if (this->m_isFlipped) {
        if (angle > -155 && angle < -90.f) {
            // Looking up
            textureCoords.y = 1;
        }
        else if (angle < 155.f && angle > 90.f) {
            // Looking down
            textureCoords.y = 2;
        }
        else {
            // Looking straight
            textureCoords.y = 0;
        }
    }
    else {
        if (angle > -90.f && angle < -25.f) {
            // Looking up
            textureCoords.y = 1;
        }
        else if (angle < 90.f && angle > 25.f) {
            // Looking down
            textureCoords.y = 2;
        }
        else {
            // Looking straight
            textureCoords.y = 0;
        }
    }

    // Play run cycle if player is moving horizontally
    if (this->m_movement.x != 0.f) {
        static float nextAnimStateChange;
        if (globals->currentTime >= nextAnimStateChange) {
            // If player is running backwards; backpedal
            if (this->m_isFlipped && this->m_movement.x > 0.f ||
                !this->m_isFlipped && this->m_movement.x < 0.f) {
                this->m_animState--;
                if (this->m_animState < 1) {
                    this->m_animState = 4;
                }
            }
            // Run normally
            else {
                this->m_animState++;
                if (this->m_animState > 4) {
                    this->m_animState = 1;
                }
            }
            nextAnimStateChange = globals->currentTime + 0.2f;
        }
    }
    else {
        this->m_animState = 0;
    }

    // Next frame
    textureCoords.x = m_animState % 5;
    textureCoords.x *= 20;
    textureCoords.y *= 32;
    this->m_sprite.setTextureRect({ textureCoords.x, textureCoords.y, 20, 32 });
}
