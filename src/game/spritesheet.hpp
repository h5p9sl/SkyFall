#pragma once

#include <SFML/Graphics.hpp>

class SpriteSheet : public sf::Texture
{
public:
    // Number of rows in the spritesheet
    const unsigned int m_rows;
    // Number of columns in the spritesheet
    const unsigned int m_columns;
    // Dimensions of a singe sprite/frame
    const sf::Vector2i m_spriteSize;
public:
    sf::IntRect getSpriteAt(unsigned int x, unsigned int y);
    sf::IntRect getSpriteAt(sf::Vector2i coords) { return this->getSpriteAt(coords.x, coords.y); }
public:
    sf::Vector2f getSpritesheetSize() {
        return sf::Vector2f(
            this->m_columns * (float)this->m_spriteSize.x,
            this->m_rows * (float)this->m_spriteSize.y
        );
    }
public:
    SpriteSheet(
        unsigned int t_rows,
        unsigned int t_columns,
        sf::Vector2i t_spriteSize
    );
    ~SpriteSheet() = default;
};

