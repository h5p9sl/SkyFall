#include "GameObjectManager.hpp"

#include <SFML/Graphics.hpp>
#include "SkyFall.h"


GameObjectManager::GameObjectManager()
{
	this->entityList.reserve(64);
}

void GameObjectManager::drawObjects(sf::RenderTarget & renderTarget)
{
	for (auto entity : this->entityList) {
		if (entity == nullptr) {
			throw std::range_error("Entity pointer was null.");
		}

		renderTarget.draw(*entity);
	}
}
