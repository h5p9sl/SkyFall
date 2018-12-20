#include "BaseGame.hpp"

#include "SkyFall.h"

BaseGame::BaseGame() :
	mainWindow(sf::VideoMode(800, 600), SkyFall::Constants::windowName)
{
}

void BaseGame::beginGameLoop()
{
	while (this->mainWindow.isOpen()) {

		sf::Event event;

		while (this->mainWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				this->mainWindow.close();
			}
		}

		this->mainWindow.clear();
		this->gameObjectManager.drawObjects(this->mainWindow);
		this->mainWindow.display();
	}
}
