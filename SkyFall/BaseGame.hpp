#pragma once
#include <SFML/Graphics.hpp>
#include "GameObjectManager.hpp"
#include "MainMenu.hpp"

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
    GameState_t gameState;
    MainMenu mainMenu;
    GameObjectManager gameObjectManager;
public:
    sf::RenderWindow mainWindow;
public:
    BaseGame();
private:
    ////////////////////////
    /// \brief Draws objects based on what the current gameState is
    ////////////////////////
    void drawGameStateCode();
    ////////////////////////
    /// \brief Draws objects based on what the current gameState is
    ////////////////////////
    void updateGameStateCode();
public:
    void beginGameLoop();
    GameState_t getGameState() { return this->gameState; }
    void setGameState(GameState_t t_gameState) { this->gameState = t_gameState; }
};
