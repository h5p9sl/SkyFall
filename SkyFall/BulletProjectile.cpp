#include "BulletProjectile.hpp"

#include "SkyFall.hpp"

bool BulletProjectile::shouldDelete()
{
    return this->m_shouldDelete;
}

BulletProjectile::BulletProjectile(
    const sf::Vector2f & src, 
    float direction, 
    float velocity) :

    m_sprite({velocity * 0.01f, 4.5f}),
    m_timeCreated(SkyFall::globals->currentTime),
    m_shouldDelete(false)
{
    this->m_sprite.setTexture(&SkyFall::globals->SPBulletTracer);
    this->m_sprite.setPosition(src);
    this->m_sprite.setRotation(direction);
    this->m_sprite.setOrigin(0.f, this->m_sprite.getSize().y / 2);

    this->m_velocity.x = cosf(direction / 180.f * SkyFall::Constants::PI) * velocity;
    this->m_velocity.y = sinf(direction / 180.f * SkyFall::Constants::PI) * velocity;
}

void BulletProjectile::draw(sf::RenderTarget & renderTarget)
{
    renderTarget.draw(this->m_sprite);
}

void BulletProjectile::update(float f_delta)
{
    sf::Vector2f newOffset = this->m_velocity * f_delta;
    this->m_sprite.move(newOffset);

    if (SkyFall::globals->currentTime - this->m_timeCreated > 1.5f) {
        this->m_shouldDelete = true;
    }
}
