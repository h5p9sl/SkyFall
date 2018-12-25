#pragma once
#include <vector>
#include "BaseEntity.hpp"

// Forward declarations
namespace sf {
    class RenderTarget;
    class Drawable;
}

class GameObjectManager
{
private:
    std::vector<BaseEntity*> entityList;
public:
    GameObjectManager();
public:
    void drawObjects(sf::RenderTarget& renderTarget);
    void updateObjects(float f_delta);
};
