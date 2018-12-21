#include "SkyFall.hpp"
#include "UIPrimitives.hpp"

using namespace SkyFall;

sf::Font* Globals::fontPLACEHOLDER = nullptr;
sf::Texture* Globals::UIButtonTexture = nullptr;

void Globals::GlobalVarInitializer::initializeVariables()
{
	if (!Globals::fontPLACEHOLDER->loadFromFile("C:\\Windows\\Fonts\\Arial.ttf")) {
		throw std::runtime_error("GlobalVarInitializer failed to open font");
	}
	if (!Globals::UIButtonTexture->loadFromFile("placeholder.txt")) {
		throw std::runtime_error("GlobalVarInitializer failed to open UIButtonTexture");
	}
}

Globals::GlobalVarInitializer::GlobalVarInitializer()
{
	Globals::fontPLACEHOLDER = new sf::Font();

	// TODO: Figure out why the "mutex" object is NULL in void GlContext::initResource()
	Globals::UIButtonTexture = new sf::Texture();

	this->initializeVariables();

}
