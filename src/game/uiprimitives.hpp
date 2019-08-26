#pragma once

#include <SFML/Graphics.hpp>

class UIButton
{
private:
    sf::Text* text;
    sf::Sprite* sprite;
public:
    UIButton(const sf::Texture& texture, const sf::IntRect& rect, const std::string& label);
    ~UIButton();
private:
    bool isMouseOnButton();
    bool isPressed();
    void highlightOnHover();
    void centerText();
public:
    ////////////////////////////////////////////////////////////
    /// \brief Updates button's dimensions and returns true if clicked.
    ////////////////////////////////////////////////////////////
    bool update();
    ////////////////////////////////////////////////////////////
    /// \brief Draws the button
    ////////////////////////////////////////////////////////////
    void draw(sf::RenderTarget& renderTarget);
public:
    void setRect(const sf::IntRect& rect) { this->sprite->setTextureRect(rect); }
};
