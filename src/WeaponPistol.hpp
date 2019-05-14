#pragma once
#include "BaseWeapon.hpp"

class SpriteSheet;

class WeaponPistol : public BaseWeapon
{
private:
    // For determining which direction the player is facing
    bool m_isFlipped;
    SpriteSheet* m_spriteSheet;
    sf::RectangleShape m_sprite;
    int m_animState;
public:
    WeaponPistol();
    ~WeaponPistol();
public:
    virtual void draw(sf::RenderTarget& renderTarget) override;
    virtual void update(float f_delta) override;
    virtual void updatePosition(sf::Vector2f& position) override;
    virtual void fire() override;
    virtual void reload() override;
private:
    void updateAnimation();
};
