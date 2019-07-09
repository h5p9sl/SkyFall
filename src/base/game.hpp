#pragma once
#include <SFML/Graphics.hpp>
#include "../game/gameobjectmanager.hpp"
#include "../mainmenu.hpp"
#include "../localplayer.hpp"
#include "scene.hpp"

enum GameState_t : uint8_t
{
    EXITING_GAME = 0,
    MAIN_MENU,
    IN_GAME,
};

/// <summary>
/// The base game manager
/// </summary>
class BaseGame
{
private:
    BaseScene* currentScene =   nullptr;
    LocalPlayer* localPlayer =  nullptr;
    // Next game state set by BaseGame::setGameState()
    GameState_t nextGameState;
    // Current game state
    GameState_t gameState;
    // Last game state
    GameState_t lastGameState;
    MainMenu mainMenu;
public:
    GameObjectManager gameObjectManager;
    sf::RenderWindow mainWindow;
public:
    BaseGame();
private:
    ////////////////////////
    /// \brief Initializes ingame objects
    ////////////////////////
    void initializeInGameObjects();
private:
    ////////////////////////
    /// \brief Draws objects based on what the current gameState is
    ////////////////////////
    void drawGameStateCode();
    ////////////////////////
    /// \brief Draws objects based on what the current gameState is
    ////////////////////////
    void updateGameStateCode(float f_delta);
public:
    LocalPlayer* getLocalPlayer() { return this->localPlayer; }
public:
    void beginGameLoop();
    GameState_t getGameState() { return this->gameState; }
    void setGameState(GameState_t t_gameState) { this->nextGameState = t_gameState; }
};
