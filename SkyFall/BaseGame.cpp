#include "BaseGame.hpp"

#include "SkyFall.hpp"
#include "LocalPlayer.hpp"

using namespace SkyFall::Constants;

BaseGame::BaseGame() :
    mainWindow(sf::VideoMode(windowSize_defualt.x, windowSize_defualt.y), windowName,
        sf::Style::Titlebar | sf::Style::Close),
    gameState(MAIN_MENU),
    nextGameState(MAIN_MENU),
    lastGameState(MAIN_MENU)
{
}

void BaseGame::initializeInGameObjects()
{
    this->localPlayer = new LocalPlayer();
    this->gameObjectManager.entityList.push_back(this->localPlayer);
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
        if (this->lastGameState != IN_GAME) {
            this->initializeInGameObjects();
        }
        this->gameObjectManager.updateObjects(f_delta);
        break;
    }
}

void BaseGame::beginGameLoop()
{
    sf::Clock clock;
    sf::Clock time;

    while (this->mainWindow.isOpen() &&
        this->gameState != GameState_t::EXITING_GAME)
    {
        // Set current time
        SkyFall::globals->currentTime = time.getElapsedTime().asSeconds();

        // Set gamestate
        this->lastGameState = this->gameState;
        this->gameState = this->nextGameState;

        // Get delta time
        float f_delta = clock.getElapsedTime().asMicroseconds() / 1000.f / 1000.f;
        clock.restart();

        // Poll window events
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
                /*
            case sf::Event::KeyPressed:
                break;
            case sf::Event::KeyReleased:
                break;
                */
            }
        }

        if (this->mainWindow.hasFocus()) {
            // Update all game objects
            this->updateGameStateCode(f_delta);

            this->mainWindow.clear(sf::Color(120, 120, 120));

            // Draw all game objects
            this->drawGameStateCode();
            this->mainWindow.display();
        }
    }
    if (this->mainWindow.isOpen()) this->mainWindow.close();
}
