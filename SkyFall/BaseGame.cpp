#include "BaseGame.hpp"

#include "SkyFall.hpp"

using namespace SkyFall::Constants;

BaseGame::BaseGame() :
	mainWindow(sf::VideoMode(windowSize_defualt.x, windowSize_defualt.y), windowName)
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
