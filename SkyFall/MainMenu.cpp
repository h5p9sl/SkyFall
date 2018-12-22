#include "MainMenu.hpp"
#include "SkyFall.hpp"

using namespace SkyFall;

MainMenu::MainMenu() :
	newButton( globals->UIButtonTexture,    {0.f,	0.f},     "New Game"),
	loadButton(globals->UIButtonTexture,    {0.f,	200.f},   "Load Game"),
	exitButton(globals->UIButtonTexture,    {0.f,	400.f},   "Exit Game")
{
}

void MainMenu::update()
{
	if (this->newButton.update()) {
		// Start new game
	}
	if (this->loadButton.update()) {
		// Load game
	}
	if (this->exitButton.update()) {
		// Exit game
	}
}

void MainMenu::draw(sf::RenderTarget & renderTarget)
{
	this->newButton.draw(renderTarget);
	this->loadButton.draw(renderTarget);
	this->exitButton.draw(renderTarget);
}
