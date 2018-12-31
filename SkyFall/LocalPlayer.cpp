#include <iostream>
#include <string>
#include "LocalPlayer.hpp"

LocalPlayer::LocalPlayer() :
    placeHolder({ 25.f, 60.f })
{
}

LocalPlayer::~LocalPlayer()
{
}

void LocalPlayer::draw(sf::RenderTarget & renderTarget)
{
    renderTarget.draw(this->placeHolder);
}

void LocalPlayer::update(float f_delta)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        this->m_velocity.y -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        this->m_velocity.y += 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        this->m_velocity.x -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        this->m_velocity.x += 1.f;
    }

    // Clamp velocity member
    this->m_velocity.y = std::max(-500.f, std::min(m_velocity.y, 500.f));
    this->m_velocity.x = std::max(-500.f, std::min(m_velocity.x, 500.f));

    // Update position member
    this->m_position += this->m_velocity * f_delta;

    // Decay velocity
    this->m_velocity *= 0.999f;

    // Update collider
    this->placeHolder.setPosition(m_position);
}
