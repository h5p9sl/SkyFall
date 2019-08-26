#include "mainmenu.hpp"
#include "skyfall.hpp"

using namespace SkyFall;

MainMenu::MainMenu()
{
    title = new sf::Text("SkyFall", globals->fontPLACEHOLDER, 100);
    title->setPosition({ 25.f, 100.f });
    title->setOutlineColor(sf::Color::Black);
    title->setOutlineThickness(2.f);

    newButton = new UIButton(globals->UIButtonTexture, {0, 300, 300, 100}, "New Game");
    loadButton = new UIButton(globals->UIButtonTexture, {0, 400, 300, 100}, "Load Game");
    exitButton = new UIButton(globals->UIButtonTexture, {0, 500, 300, 100}, "Exit Game");
}

MainMenu::~MainMenu() {
    delete newButton;
    delete loadButton;
    delete exitButton;
}

void MainMenu::drawLoadGamePrompt(sf::RenderTarget & renderTarget)
{
    
}

void MainMenu::update()
{
    if (globals->musicMainMenu.getStatus() != sf::Music::Status::Playing) {
        globals->musicMainMenu.play();
    }

    if (this->newButton->update()) {
        // Start new game
        globals->musicMainMenu.stop();
        globals->baseGame->setGameState(GameState_t::IN_GAME);
    }
    if (this->loadButton->update()) {
        // Load game
        globals->musicMainMenu.stop();
        // TODO: Implement
        //globals->gameSaveManager->loadGameSaves();
        this->b_shouldDrawLoadGamePrompt = true;
    }
    if (this->exitButton->update()) {
        // Exit game
        globals->musicMainMenu.stop();
        globals->baseGame->setGameState(GameState_t::EXITING_GAME);
    }
}

void MainMenu::draw(sf::RenderTarget & renderTarget)
{
    this->newButton->draw(renderTarget);
    this->loadButton->draw(renderTarget);
    this->exitButton->draw(renderTarget);

    if (this->b_shouldDrawLoadGamePrompt) this->drawLoadGamePrompt(renderTarget);

    renderTarget.draw(*this->title);
}
