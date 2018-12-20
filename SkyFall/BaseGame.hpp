#pragma once
#include <SFML/Graphics.hpp>
#include "GameObjectManager.hpp"

/// <summary>
/// The base game manager
/// </summary>
class BaseGame
{
private:
	sf::RenderWindow mainWindow;
	GameObjectManager gameObjectManager;
public:
	BaseGame();
public:
	void beginGameLoop();
};