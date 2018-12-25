#pragma once
#include <vector>
#include "BaseObject.hpp"

// Forward declarations
namespace sf {
    class RenderTarget;
    class Drawable;
}

class GameObjectManager
{
private:
    std::vector<BaseObject*> entityList;
public:
    GameObjectManager();
public:
    void drawObjects(sf::RenderTarget& renderTarget);
    void updateObjects(float f_delta);
};
