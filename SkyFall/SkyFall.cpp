#include "SkyFall.hpp"
#include "UIPrimitives.hpp"

using namespace SkyFall;

SkyFall::GlobalVariables* SkyFall::globals = nullptr;

SkyFall::GlobalVariables::GlobalVariables()
{
    if (!this->fontPLACEHOLDER.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf")) {
        throw std::runtime_error("failed to open font");
    }
    if (!this->UIButtonTexture.loadFromFile("button.png")) {
        throw std::runtime_error("failed to open UIButtonTexture");
    }
    /*if (!this->musicMainMenu.openFromFile("MainMenu.ogg")) {
        throw std::runtime_error("failed to open musicMainMenu");
    }*/
}
