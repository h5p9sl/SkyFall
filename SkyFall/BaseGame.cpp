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

void BaseGame::updateGameStateCode(float f_delta)
{
    switch (this->gameState)
    {
    case EXITING_GAME:
        break;
    case MAIN_MENU:
        this->mainMenu.update();
        break;
    case IN_GAME:
        this->gameObjectManager.updateObjects(f_delta);
        break;
    }
}

void BaseGame::beginGameLoop()
{
    sf::Clock clock;

    while (this->mainWindow.isOpen() &&
        this->gameState != GameState_t::EXITING_GAME)
    {
        float f_delta = clock.getElapsedTime().asMilliseconds() / 1000.f;
        clock.restart();

        sf::Event event;

        while (this->mainWindow.pollEvent(event)) {
            switch (event.type)
            {
            case sf::Event::Closed:
                this->mainWindow.close();
                break;

            case sf::Event::Resized:
                sf::Vector2i oldPosition = this->mainWindow.getPosition();
                
                // Re-create window
                this->mainWindow.create(
                    sf::VideoMode(event.size.width, event.size.height),
                    SkyFall::Constants::windowName
                );

                this->mainWindow.setPosition(oldPosition);
                
                break;
            }
        }

        // Update all game objects
        this->updateGameStateCode(f_delta);

        this->mainWindow.clear();
        // Draw all game objects
        this->drawGameStateCode();
        this->mainWindow.display();
    }
    if (this->mainWindow.isOpen()) this->mainWindow.close();
}
