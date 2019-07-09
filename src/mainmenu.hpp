#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "UIPrimitives.hpp"

class MainMenu
{
private:
    sf::Text title;
    UIButton newButton;
    UIButton loadButton;
    UIButton exitButton;
private:
    bool b_shouldDrawLoadGamePrompt = false;
public:
    MainMenu();
public:
    void drawLoadGamePrompt(sf::RenderTarget& renderTarget);
public:
    void update();
    void draw(sf::RenderTarget& renderTarget);
};
