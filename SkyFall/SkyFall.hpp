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
	class Globals
	{
	public:
		////////////////////////////////////////////////////////////
		/// \brief Initializes global members
		////////////////////////////////////////////////////////////
		Globals();
	public:
		static sf::Texture& UIButtonTexture;
		static sf::Font& fontPLACEHOLDER;
	};
};