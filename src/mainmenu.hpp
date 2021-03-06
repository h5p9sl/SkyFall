#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "game/uiprimitives.hpp"

class MainMenu
{
private:
    sf::Text* title;
    UIButton* newButton;
    UIButton* loadButton;
    UIButton* exitButton;
private:
    bool b_shouldDrawLoadGamePrompt = false;
public:
    MainMenu();
    ~MainMenu();
public:
    void drawLoadGamePrompt(sf::RenderTarget& renderTarget);
public:
    void update();
    void draw(sf::RenderTarget& renderTarget);
};
