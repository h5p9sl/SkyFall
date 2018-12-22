#pragma once

#include <string>
#include <exception>

#include <SFML/Graphics.hpp>

namespace SkyFall
{
	namespace Constants
	{
		static const char* windowName = "SkyFall";
		static const sf::Vector2u windowSize_defualt = {800u, 600u};
	};

    class GlobalVariables
    {
    public:
        sf::RenderWindow* mainWindow;
        sf::Texture UIButtonTexture;
        sf::Font fontPLACEHOLDER;
    public:
        GlobalVariables();
    };
    
    extern GlobalVariables* globals;

};
