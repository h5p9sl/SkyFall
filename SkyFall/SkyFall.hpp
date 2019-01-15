#pragma once

#include <string>
#include <exception>

#include <SFML/Graphics.hpp>

#include "BaseGame.hpp"
#include "GameSaveManager.hpp"

namespace SkyFall
{
    namespace Constants
    {
        static const float PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062f;
        static const char* windowName = "SkyFall";
        static const sf::Vector2u windowSize_defualt = {1024u, 576u};
        static const float globalGravity = 15.f;
    };

    class GlobalVariables
    {
    public:
        float currentTime;
    public:
        BaseGame* baseGame;
        GameSaveManager* gameSaveManager;
    private:
        sf::SoundBuffer SFBPistolShoot1;
    public:
        sf::Sound SFXPistolShoot1;
    public:
        sf::Music musicMainMenu;
    public:
        sf::Texture SPBulletTracer;
        sf::Texture SPPlayer;
        sf::Texture SPPistol;
        sf::Texture UIButtonTexture;
        sf::Font fontPLACEHOLDER;
    public:
        GlobalVariables();
        void initializeGlobals();
    };
    
    extern GlobalVariables* globals;

};
