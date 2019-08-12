#pragma once
#include "../base/object.hpp"

class PhysicsObject : public BaseObject
{
protected:
    float mass;
public:
    //virtual void onCollide(PhysicsObject& collider) = 0;
};