#pragma once

#include <SFML/Graphics.hpp>

class UIButton
{
private:
    static const uint8_t highlightAmount = 100;
    bool lastHighlightState = false;
    sf::Color lastHighlightColor;
private:
    sf::Text text;
    sf::Sprite sprite;
public:
    UIButton(const sf::Texture& texture, const sf::Vector2f& pos, const std::string& label);
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
    void setRect(const sf::IntRect& rect) { this->sprite.setTextureRect(rect); }
};
