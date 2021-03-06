#include "enemy.hpp"
#include "game/spritesheet.hpp"

#include "skyfall.hpp"

#include <cmath>

using namespace SkyFall;

Enemy::Enemy() :
    m_spriteSheet(&globals->SPEnemy01)
{
    // Initialize m_sprite size
    this->m_sprite.setSize(
        sf::Vector2f(
            this->m_spriteSheet->m_spriteSize.x * 4.f,
            this->m_spriteSheet->m_spriteSize.y * 4.f
        )
    );

    // Set origin
    sf::FloatRect bottomCenter = this->m_sprite.getLocalBounds();
    bottomCenter.left += bottomCenter.width / 2.f;
    bottomCenter.top += bottomCenter.height;
    m_sprite.setOrigin(bottomCenter.left, bottomCenter.top);
}

Enemy::~Enemy() {
}

void Enemy::draw(sf::RenderTarget& renderTarget) {
    renderTarget.draw(this->m_sprite);
}

void Enemy::update(float f_delta) {
    this->updatePhysics(f_delta);
    this->updateAnimation();
}

void Enemy::updateAnimation() {
    LocalPlayer* player = globals->baseGame->getLocalPlayer();
    if (player == nullptr) return;

    sf::Vector2f ppos = player->getPosition();
    sf::Vector2f vec = ppos - this->m_position;
    vec /= hypotf(vec.x, vec.y);

    if (vec.x > 0.f) {
        // Player is behind enemy
        this->m_sprite.setScale({ -1.f, 1.f });
        this->m_isFlipped = true;
    } else {
        // Player is in front of enemy
        this->m_sprite.setScale({ 1.f, 1.f });
        this->m_isFlipped = false;
    }

    // Set sprite texture
    this->m_sprite.setTexture(this->m_spriteSheet);
}

void Enemy::updatePhysics(float f_delta) {
    this->m_velocity.y += Constants::globalGravity;

    if (this->m_position.y >= globals->baseGame->mainWindow.getView().getSize().y)
    {
        this->m_position.y = globals->baseGame->mainWindow.getView().getSize().y;
        this->m_velocity.y = 0;
    } else {
        this->m_position += this->m_velocity * f_delta;
    }

    this->m_sprite.setPosition(this->m_position);
}

