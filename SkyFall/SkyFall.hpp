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

	namespace Globals
	{
		////////////////////////////////////////////////////////////
		/// \brief Initializes global variables
		////////////////////////////////////////////////////////////
		class GlobalVarInitializer
		{
		public:
			GlobalVarInitializer();
		};

		static sf::Texture* UIButtonTexture =	nullptr;
		static sf::Font* fontPLACEHOLDER =		nullptr;
	};
};
