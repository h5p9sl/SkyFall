#include <iostream>
#include <string>
#include "LocalPlayer.hpp"

#include "WeaponPistol.hpp"

#include "SkyFall.hpp"

using namespace SkyFall;

// TODO: Remove this when done debugging
sf::Texture* playerSprites[8] = { nullptr };
static int playerSpriteIndex = 0;

LocalPlayer::LocalPlayer() :
    m_sprite({ 20.f * 4, 32.f * 4 }),
    m_enablePlayerControls(true)
{
    playerSprites[0] = &globals->SPPlayer_Gas1Dark;
    playerSprites[1] = &globals->SPPlayer_Gas1Light;
    playerSprites[2] = &globals->SPPlayer_Gas2Dark;
    playerSprites[3] = &globals->SPPlayer_Gas2Light;
    playerSprites[4] = &globals->SPPlayer_OriginalDark;
    playerSprites[5] = &globals->SPPlayer_OriginalLight;
    playerSprites[6] = &globals->SPPlayer_KiverDark;
    playerSprites[7] = &globals->SPPlayer_KiverLight;
    m_sprite.setTexture(playerSprites[0]);
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

        // Cycle through spritesheets **FOR DEBUGGING**
        if (Input::wasKeyPressed(sf::Keyboard::Right)) {
            if (playerSpriteIndex >= 7) playerSpriteIndex = -1;
            this->m_sprite.setTexture(playerSprites[++playerSpriteIndex]);
        }
        if (Input::wasKeyPressed(sf::Keyboard::Left)) {
            if (playerSpriteIndex <= 0) playerSpriteIndex = 8;
            this->m_sprite.setTexture(playerSprites[--playerSpriteIndex]);
        }

        // Update movement vector
        if (Input::isKeyPressed(sf::Keyboard::W) && this->m_onGround) {
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
        sf::Vector2f mousePosition = globals->baseGame->mainWindow.getView().getCenter();
        float vector = mousePosition.x - this->m_position.x;
        if (vector < 0.f) {
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

void LocalPlayer::updateCamera(sf::RenderWindow& parentWindow)
{
    sf::Vector2u windowSize = parentWindow.getSize();
    sf::Vector2f f_windowSize = { (float)windowSize.x, (float)windowSize.y };

    sf::Vector2f cameraPosition = this->getPosition();
    cameraPosition.y -= 18.f * 4.f;
                
    sf::Vector2i mousePosition = sf::Mouse::getPosition(parentWindow);
    // Clamp mouse position to the size of the window
    mousePosition.x = std::min(std::max(mousePosition.x, 0), (int)windowSize.x);
    mousePosition.y = std::min(std::max(mousePosition.y, 0), (int)windowSize.y);
                
    sf::Vector2f f_mousePosition = { (float)mousePosition.x, (float)mousePosition.y };
    // Offset mouse position by half the size of the window
    f_mousePosition.x -= f_windowSize.x / 2.f;
    f_mousePosition.y -= f_windowSize.y / 2.f;
                
    float xV = f_mousePosition.x / f_windowSize.x;
    float yV = f_mousePosition.y / f_windowSize.y;
    float hV = 1.f - hypotf(xV, yV);

    // Offset camera position by vector of mousePosition
    cameraPosition += f_mousePosition * hV;
                
    parentWindow.setView(sf::View(cameraPosition, f_windowSize));
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
    if (this->currentWeapon != nullptr) {
        this->currentWeapon->updatePosition(armPosition);
    }

    // Get normalized vector between mouse and player position
    // sf::Vector2i mousePosition = sf::Mouse::getPosition(globals->baseGame->mainWindow);
    sf::Vector2f mousePosition = globals->baseGame->mainWindow.getView().getCenter();
    sf::Vector2f mvec = { (float)mousePosition.x - armPosition.x, (float)mousePosition.y - armPosition.y };
    float hyp = hypotf(mvec.x, mvec.y);
    mvec.x /= hyp;
    mvec.y /= hyp;
    // Variable to store coordinates for spritesheet
    sf::Vector2i textureCoords;
    if (mvec.y <= -0.5f) {
        textureCoords.y = 1; // Looking up
    }
    else if (mvec.y >= 0.5f) {
        textureCoords.y = 2; // Looking down
    }
    else {
        textureCoords.y = 0; // Looking straight
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
                    this->m_animState = 6;
                }
            }
            // Run normally
            else {
                this->m_animState++;
                if (this->m_animState > 6) {
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
    textureCoords.x = m_animState;
    textureCoords.x *= 20;
    textureCoords.y *= 32;
    this->m_sprite.setTextureRect({ textureCoords.x, textureCoords.y, 20, 32 });
}
