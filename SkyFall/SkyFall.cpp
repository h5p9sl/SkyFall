#include "SkyFall.hpp"
#include "UIPrimitives.hpp"

using namespace SkyFall;

SkyFall::GlobalVariables* SkyFall::globals = nullptr;

SkyFall::GlobalVariables::GlobalVariables()
{
    if (!this->fontPLACEHOLDER.loadFromFile("../GFX/font/bebas_neue/BebasNeue-Regular.ttf")) {
        throw std::runtime_error("failed to open font");
    }
    if (!this->UIButtonTexture.loadFromFile("../GFX/button.png")) {
        throw std::runtime_error("failed to open UIButtonTexture");
    }
    if (!this->musicMainMenu.openFromFile("../SFX/MainMenu.ogg")) {
        throw std::runtime_error("failed to open musicMainMenu");
    }
    else {
        this->musicMainMenu.setLoop(true);
    }
}

void SkyFall::GlobalVariables::initializeGlobals()
{
    this->baseGame = new BaseGame();
    this->gameSaveManager = new GameSaveManager();
}
