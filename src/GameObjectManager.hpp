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
public:
    std::vector<BaseObject*> entityList;
public:
    GameObjectManager();
public:
    void drawObjects(sf::RenderTarget& renderTarget);
    void updateObjects(float f_delta);
public:
    void __inline addEntity(BaseObject* entity) {
        this->entityList.emplace_back(entity);
    }
};
