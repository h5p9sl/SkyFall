#include "SkyFall.hpp"
#include "UIPrimitives.hpp"

using namespace SkyFall;

SkyFall::GlobalVariables* SkyFall::globals = nullptr;

SkyFall::GlobalVariables::GlobalVariables()
{
    // LOAD GFX
    if (!this->UIButtonTexture.loadFromFile("../GFX/button.png")) {
        throw std::runtime_error("failed to open UIButtonTexture");
    }
    if (!this->SPPlayer.loadFromFile("../GFX/Player.png")) {
        throw std::runtime_error("failed to open SPPlayer");
    }
    if (!this->SPPistol.loadFromFile("../GFX/PlayerPistol.png")) {
        throw std::runtime_error("failed to open SPPistol");
    }

    // LOAD SFX
    if (!this->musicMainMenu.openFromFile("../SFX/MainMenu.ogg")) {
        throw std::runtime_error("failed to open musicMainMenu");
    }
    else {
        this->musicMainMenu.setLoop(true);
    }

    // LOAD OTHER
    if (!this->fontPLACEHOLDER.loadFromFile("../GFX/font/bebas_neue/BebasNeue-Regular.ttf")) {
        throw std::runtime_error("failed to open font");
    }
}

void SkyFall::GlobalVariables::initializeGlobals()
{
    this->baseGame = new BaseGame();
    this->gameSaveManager = new GameSaveManager();
}
