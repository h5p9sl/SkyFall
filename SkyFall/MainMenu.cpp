#include "MainMenu.hpp"
#include "SkyFall.hpp"

using namespace SkyFall;

MainMenu::MainMenu() :
    newButton( globals->UIButtonTexture,    {0, 300, 400, 100}, "New Game"),
    loadButton(globals->UIButtonTexture,    {0, 400, 400, 100}, "Load Game"),
    exitButton(globals->UIButtonTexture,    {0, 500, 400, 100}, "Exit Game"),
    title("SkyFall", globals->fontPLACEHOLDER, 100)
{
    title.setPosition({ 25.f, 100.f });
    title.setOutlineColor(sf::Color::Black);
    title.setOutlineThickness(2.f);
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
        globals->baseGame->setGameState(GameState_t::EXITING_GAME);
    }
}

void MainMenu::draw(sf::RenderTarget & renderTarget)
{
    this->newButton.draw(renderTarget);
    this->loadButton.draw(renderTarget);
    this->exitButton.draw(renderTarget);

    renderTarget.draw(this->title);
}
