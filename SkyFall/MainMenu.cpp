#include "MainMenu.hpp"
#include "SkyFall.hpp"

using namespace SkyFall;

MainMenu::MainMenu() :
	newButton( globals->UIButtonTexture,    {0,	0},     "New Game"),
	loadButton(globals->UIButtonTexture,    {0,	200},   "Load Game"),
	exitButton(globals->UIButtonTexture,    {0,	400},   "Exit Game")
{
    newButton.setRect({  0, 0, 300, 200 });
    loadButton.setRect({ 0, 0, 300, 200 });
    exitButton.setRect({ 0, 0, 300, 200 });
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
