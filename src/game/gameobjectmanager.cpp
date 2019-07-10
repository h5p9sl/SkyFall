#include "gameobjectmanager.hpp"

#include <SFML/Graphics.hpp>
#include "../skyfall.hpp"


GameObjectManager::GameObjectManager()
{
    this->entityList.reserve(64);
}

void GameObjectManager::drawObjects(sf::RenderTarget & renderTarget)
{
    for (auto& entity : this->entityList) {
        if (entity == nullptr) {
            throw std::range_error("Entity pointer was null.");
            continue;
        }

        entity->draw(renderTarget);
    }
}

void GameObjectManager::updateObjects(float f_delta)
{
    for (auto& entity : this->entityList) {
        if (entity == nullptr) {
            throw std::range_error("Entity pointer was null.");
            continue;
        }

        entity->update(f_delta);
    }
}
