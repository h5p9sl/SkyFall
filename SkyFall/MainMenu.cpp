#include "MainMenu.hpp"
#include "SkyFall.hpp"

using namespace SkyFall;

MainMenu::MainMenu() :
	newButton( *Globals::UIButtonTexture,   {0,	0},		"New Game"),
	loadButton(*Globals::UIButtonTexture,	{0,	200},	"Load Game"),
	exitButton(*Globals::UIButtonTexture,	{0,	400},	"Exit Game")
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
