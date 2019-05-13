#pragma once

#include <string>
#include <exception>

#include <SFML/Graphics.hpp>
#include <math.h>

#include "Scenes.hpp"
#include "BaseGame.hpp"
#include "GameSaveManager.hpp"
#include "Input.hpp"

namespace SkyFall
{
    namespace Constants
    {
        static const float PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062f;
        static const char* windowName = "SkyFall";
        static const sf::Vector2u windowSize_defualt = {800u, 600u};
        static const float globalGravity = 15.f;
    };

    namespace Scenes
    {
        class Scene1;
    };

    class GlobalVariables
    {
    public:
        float currentTime;
    public:
        BaseGame* baseGame;
        Input* inputSystem;
        GameSaveManager* gameSaveManager;
    private:
        sf::SoundBuffer SFBPistolShoot1;
    public:
        sf::Sound SFXPistolShoot1;
    public:
        sf::Music musicMainMenu;
    public:
        sf::Texture SPScene1Background;
        sf::Texture SPBulletTracer;
        sf::Texture SPPlayer_Gas1Dark;
        sf::Texture SPPlayer_Gas1Light;
        sf::Texture SPPlayer_Gas2Dark;
        sf::Texture SPPlayer_Gas2Light;
        sf::Texture SPPlayer_OriginalDark;
        sf::Texture SPPlayer_OriginalLight;
        sf::Texture SPPlayer_KiverDark;
        sf::Texture SPPlayer_KiverLight;
        sf::Texture SPPistol;
        sf::Texture UIButtonTexture;
        sf::Font fontPLACEHOLDER;
    public:
        GlobalVariables();
        ~GlobalVariables();
        void initializeGlobals();
    };
    
    extern GlobalVariables* globals;

};
