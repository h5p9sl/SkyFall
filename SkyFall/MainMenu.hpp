#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "UIPrimitives.hpp"

class MainMenu
{
private:
    UIButton newButton;
    UIButton loadButton;
    UIButton exitButton;
public:
    MainMenu();
public:
    void update();
    void draw(sf::RenderTarget& renderTarget);
};
