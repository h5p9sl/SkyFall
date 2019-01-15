#include "SkyFall.hpp"
#include "UIPrimitives.hpp"
#include <iostream>

using namespace SkyFall;

SkyFall::GlobalVariables* SkyFall::globals = nullptr;

SkyFall::GlobalVariables::GlobalVariables()
{
    std::cout << "Loading assets..." << std::endl;

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
    if (!this->SPBulletTracer.loadFromFile("../GFX/BulletTracer.png")) {
        throw std::runtime_error("failed to open SPBulletTracer");
    }

    // LOAD SFX
    if (!this->musicMainMenu.openFromFile("../SFX/MainMenu.ogg")) {
        throw std::runtime_error("failed to open musicMainMenu");
    } else {
        this->musicMainMenu.setLoop(true);
    }

    if (!this->SFBPistolShoot1.loadFromFile("../SFX/PistolShoot1.ogg")) {
        throw std::runtime_error("failed to open musicMainMenu");
    } else {
        this->SFXPistolShoot1.setBuffer(this->SFBPistolShoot1);
    }

    // LOAD OTHER
    if (!this->fontPLACEHOLDER.loadFromFile("../GFX/font/bebas_neue/BebasNeue-Regular.ttf")) {
        throw std::runtime_error("failed to open font");
    }
}

SkyFall::GlobalVariables::~GlobalVariables()
{
    if (this->inputSystem) delete this->inputSystem;
    if (this->gameSaveManager) delete this->gameSaveManager;
    if (this->baseGame) delete this->baseGame;
}

void SkyFall::GlobalVariables::initializeGlobals()
{
    std::cout << "Initializing CBaseGame..." << std::endl;
    this->baseGame = new BaseGame();
    std::cout << "Initializing GameSaveManager..." << std::endl;
    this->gameSaveManager = new GameSaveManager();
}
