#include "BaseGame.hpp"

#include "SkyFall.hpp"

using namespace SkyFall::Constants;

BaseGame::BaseGame() :
	mainWindow(sf::VideoMode(windowSize_defualt.x, windowSize_defualt.y), windowName),
	gameState(MAIN_MENU)
{
}

void BaseGame::drawGameStateCode()
{
	switch (this->gameState)
	{
	case MAIN_MENU:
		this->mainMenu.draw(this->mainWindow);
		break;
	case IN_GAME:
		this->gameObjectManager.drawObjects(this->mainWindow);
		break;
	}
}

void BaseGame::updateGameStateCode()
{
	switch (this->gameState)
	{
    case EXITING_GAME:
        break;
	case MAIN_MENU:
		this->mainMenu.update();
		break;
	case IN_GAME:
		// TODO: create actual delta time
		this->gameObjectManager.updateObjects(0.1f);
		break;
	}
}

void BaseGame::beginGameLoop()
{
	while (this->mainWindow.isOpen() &&
        this->gameState != GameState_t::EXITING_GAME)
    {

		sf::Event event;

		while (this->mainWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				this->mainWindow.close();
			}
		}

		// Update all game objects
		this->updateGameStateCode();

		this->mainWindow.clear();
		// Draw all game objects
		this->drawGameStateCode();
		this->mainWindow.display();
	}
}
