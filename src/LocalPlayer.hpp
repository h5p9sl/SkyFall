#pragma once
#include "BaseEntity.hpp"
#include "BaseWeapon.hpp"
#include "PhysicsObject.hpp"
#include <vector>

class LocalPlayer : public BaseEntity
{
private:
    // For determining which direction the player is facing
    bool m_enablePlayerControls;
    bool m_isFlipped;
    sf::RectangleShape m_sprite;
    sf::Vector2f m_velocity;
    sf::Vector2f m_movement;
    int m_animState;
private:
    BaseWeapon* currentWeapon;
    std::vector<BaseWeapon*> weapons;
public:
    LocalPlayer();
    ~LocalPlayer();
public:
    virtual void draw(sf::RenderTarget& renderTarget) override;
    virtual void update(float f_delta) override;
    void updateCamera(sf::RenderWindow& parentWindow);
private:
    void updatePhysics(float f_delta);
    void updateAnimation();
};
