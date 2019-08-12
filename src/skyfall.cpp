#include "skyfall.hpp"
#include "game/uiprimitives.hpp"
#include <iostream>
#include <string>

using namespace SkyFall;

SkyFall::GlobalVariables* SkyFall::globals = nullptr;

bool __inline loadGFXAsset(sf::Texture& t_resource, const std::string& t_directory);
bool __inline loadGFXAsset(sf::Font& t_resource, const std::string& t_directory);
bool __inline loadSFXAsset(sf::Music& t_resource, const std::string& t_directory);
bool __inline loadSFXAsset(sf::SoundBuffer& t_resource, const std::string& t_directory);

SkyFall::GlobalVariables::GlobalVariables()
:
    // Player Sprites
    SPPlayer_Gas1Dark(3, 7, {20, 32}),
    SPPlayer_Gas1Light(3, 7, {20, 32}),
    SPPlayer_Gas2Dark(3, 7, {20, 32}),
    SPPlayer_Gas2Light(3, 7, {20, 32}),
    SPPlayer_OriginalDark(3, 7, {20, 32}),
    SPPlayer_OriginalLight(3, 7, {20, 32}),
    SPPlayer_KiverDark(3, 7, {20, 32}),
    SPPlayer_KiverLight(3, 7, {20, 32}),
    SPPistol(1, 3, {16, 9}),
    SPEnemy01(1, 1, {27, 33})
{
    std::cout << "Loading assets..." << std::endl;

    // LOAD GFX
    loadGFXAsset(this->UIButtonTexture,         "../GFX/button.png");
    loadGFXAsset(this->SPPlayer_Gas1Dark,       "../GFX/player/Gas1Dark.png");
    loadGFXAsset(this->SPPlayer_Gas1Light,      "../GFX/player/Gas1Light.png");
    loadGFXAsset(this->SPPlayer_Gas2Dark,       "../GFX/player/Gas2Dark.png");
    loadGFXAsset(this->SPPlayer_Gas2Light,      "../GFX/player/Gas2Light.png");
    loadGFXAsset(this->SPPlayer_OriginalDark,   "../GFX/player/OriginalDark.png");
    loadGFXAsset(this->SPPlayer_OriginalLight,  "../GFX/player/OriginalLight.png");
    loadGFXAsset(this->SPPlayer_KiverDark,      "../GFX/player/KiverDark.png");
    loadGFXAsset(this->SPPlayer_KiverLight,     "../GFX/player/KiverLight.png");
    loadGFXAsset(this->SPPistol,                "../GFX/PlayerPistol.png");
    loadGFXAsset(this->SPBulletTracer,          "../GFX/BulletTracer.png");
    loadGFXAsset(this->SPScene1Background,      "../GFX/Scene1Background.png");
    loadGFXAsset(this->SPEnemy01,               "../GFX/enemies/enemy01.png");

    // LOAD SFX
    if (loadSFXAsset(this->musicMainMenu,       "../SFX/Skullcrusher.ogg")) {
        this->musicMainMenu.setLoop(true);
    }
    if (loadSFXAsset(this->musicBackground01,    "../SFX/BG01.ogg")) {
        this->musicBackground01.setLoop(true);
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
