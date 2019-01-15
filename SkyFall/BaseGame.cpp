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
    this->mainWindow.setFramerateLimit(60u);
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
        float f_delta = clock.getElapsedTime().asMilliseconds() / 1000.f;
        clock.restart();

        // Update input states
        Input::updateStates();

        // Poll window events
        sf::Event event;
        while (this->mainWindow.pollEvent(event)) {
            switch (event.type)
            {
            case sf::Event::Closed:
                this->mainWindow.close();
                break;
            case sf::Event::KeyPressed:
                Input::onKeyDown(event.key.code);
                break;
            case sf::Event::KeyReleased:
                Input::onKeyUp(event.key.code);
                break;
            case sf::Event::MouseButtonPressed:
                Input::onButtonDown(event.mouseButton.button);
                break;
            case sf::Event::MouseButtonReleased:
                Input::onButtonUp(event.mouseButton.button);
                break;
            }
        }

        if (this->mainWindow.hasFocus()) {
            // Update all game objects
            this->updateGameStateCode(f_delta);

            // TODO: Make this less janky
            // Update camera
            if (this->localPlayer != nullptr) {
                
                sf::Vector2f cameraPosition = this->localPlayer->getPosition();
                cameraPosition.y -= 18.f * 4.f;
                
                sf::Vector2i mousePosition = sf::Mouse::getPosition(this->mainWindow);
                sf::Vector2f f_mousePosition = { (float)mousePosition.x, (float)mousePosition.y };
                // Offset mouse position by half the size of the window
                f_mousePosition.x -= 800.f / 2.f;
                f_mousePosition.y -= 600.f / 2.f;
                
                // Offset camera position by hypotenuse of mousePosition
                sf::Vector2f vector = cameraPosition - f_mousePosition;

                cameraPosition += f_mousePosition;
                
                this->mainWindow.setView(sf::View(cameraPosition, { 800.f, 600.f }));
            }

            this->mainWindow.clear(sf::Color(0x31, 0x41, 0x59));

            // Draw all game objects
            this->drawGameStateCode();
            this->mainWindow.display();
        }
    }
    if (this->mainWindow.isOpen()) this->mainWindow.close();
}
