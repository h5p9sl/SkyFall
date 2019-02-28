#include "SkyFall.hpp"
#include "UIPrimitives.hpp"
#include <iostream>
#include <string>

using namespace SkyFall;

SkyFall::GlobalVariables* SkyFall::globals = nullptr;

bool __inline loadGFXAsset(sf::Texture& t_resource, const std::string& t_directory);
bool __inline loadGFXAsset(sf::Font& t_resource, const std::string& t_directory);
bool __inline loadSFXAsset(sf::Music& t_resource, const std::string& t_directory);
bool __inline loadSFXAsset(sf::SoundBuffer& t_resource, const std::string& t_directory);

SkyFall::GlobalVariables::GlobalVariables()
{
    std::cout << "Loading assets..." << std::endl;

    // LOAD GFX
    loadGFXAsset(this->UIButtonTexture,         "../GFX/button.png");
    loadGFXAsset(this->SPPlayer,                "../GFX/Player.png");
    loadGFXAsset(this->SPPistol,                "../GFX/PlayerPistol.png");
    loadGFXAsset(this->SPBulletTracer,          "../GFX/BulletTracer.png");
    loadGFXAsset(this->SPScene1Background,      "../GFX/Scene1Background.png");

    // LOAD SFX
    if (loadSFXAsset(this->musicMainMenu,       "../SFX/MainMenu.ogg")) {
        this->musicMainMenu.setLoop(true);
    }
    if (loadSFXAsset(this->SFBPistolShoot1,     "../SFX/PistolShoot1.ogg")) {
        this->SFXPistolShoot1.setBuffer(this->SFBPistolShoot1);
    }

    // LOAD OTHER
    loadGFXAsset(this->fontPLACEHOLDER,         "../GFX/font/bebas_neue/BebasNeue-Regular.ttf");
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







bool __inline loadGFXAsset(sf::Texture& t_resource, const std::string& t_directory) {
    if (!t_resource.loadFromFile(t_directory)) {
        throw std::runtime_error("Failed to open " + t_directory);
        return false;
    }
    return true;
}

bool __inline loadGFXAsset(sf::Font & t_resource, const std::string & t_directory)
{
    if (!t_resource.loadFromFile(t_directory)) {
        throw std::runtime_error("Failed to open " + t_directory);
        return false;
    }
    return true;
}

bool __inline loadSFXAsset(sf::Music& t_resource, const std::string& t_directory) {
    if (!t_resource.openFromFile(t_directory)) {
        throw std::runtime_error("Failed to open " + t_directory);
        return false;
    }
    return true;
}

bool __inline loadSFXAsset(sf::SoundBuffer& t_resource, const std::string& t_directory) {
    if (!t_resource.loadFromFile(t_directory)) {
        throw std::runtime_error("Failed to open " + t_directory);
        return false;
    }
    return true;
}
