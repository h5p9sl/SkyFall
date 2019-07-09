#pragma once

// Forward declarations
namespace sf {
    class RenderTarget;
    class Drawable;
}

// Pure virtual class
class BaseObject
{
public:
    virtual void draw(sf::RenderTarget& renderTarget) = 0;
    virtual void update(float f_delta) = 0;
};