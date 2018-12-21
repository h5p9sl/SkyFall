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
		private:
			void initializeVariables();
		public:
			GlobalVarInitializer();
		} static globalVarInitializer;

		extern sf::Texture* UIButtonTexture;
		extern sf::Font* fontPLACEHOLDER;
	};
};
