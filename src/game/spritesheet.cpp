#include "spritesheet.hpp"

#include <iostream>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

SpriteSheet::SpriteSheet(
    unsigned int t_rows,
    unsigned int t_columns,
    sf::Vector2i t_spriteSize
)
:
    m_rows(t_rows),
    m_columns(t_columns),
    m_spriteSize(t_spriteSize)
{
}

sf::IntRect SpriteSheet::getSpriteAt(unsigned int x, unsigned int y) {
    if (x > this->m_columns) {
        std::cerr << "ERROR in SpriteSheet::getSpriteAt(unsigned,unsigned). 'x' is greater than number of columns.\n";
    }
    else if (y > this->m_rows) {
        std::cerr << "ERROR in SpriteSheet::getSpriteAt(unsigned,unsigned). 'x' is greater than number of columns.\n";
    }
    else {
        return sf::IntRect(
            x * this->m_spriteSize.x,
            y * this->m_spriteSize.y,
            this->m_spriteSize.x,
            this->m_spriteSize.y
        );
    }
    return sf::IntRect();
}

