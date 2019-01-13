#include "BulletProjectile.hpp"

#include "SkyFall.hpp"

BulletProjectile::BulletProjectile(
    const sf::Vector2f & src, 
    float direction, 
    float velocity) :

    velocity(velocity),
    sprite({velocity * 0.01f, 4.5f}),
    timeCreated(SkyFall::globals->currentTime)
{
    this->sprite.setTexture(&SkyFall::globals->SPBulletTracer);
    this->sprite.setPosition(src);
    this->sprite.setRotation(direction);
    this->sprite.setOrigin(0.f, this->sprite.getSize().y / 2);

    this->direction.x = cosf(direction / 180.f * SkyFall::Constants::PI);
    this->direction.y = sinf(direction / 180.f * SkyFall::Constants::PI);
}

void BulletProjectile::draw(sf::RenderTarget & renderTarget)
{
    renderTarget.draw(this->sprite);
}

void BulletProjectile::update(float f_delta)
{
    sf::Vector2f newOffset = this->direction * velocity * f_delta;
    this->sprite.move(newOffset);

    if (SkyFall::globals->currentTime - this->timeCreated > 1.5f) {
        this->shouldDelete = true;
    }
}
