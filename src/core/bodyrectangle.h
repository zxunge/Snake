// SPDX-License-Identifier: MIT

#ifndef BODYRECTANGLE_H
#define BODYRECTANGLE_H

#include "globaldefs.h"

#include <SFML/Graphics.hpp>

#include <SFML/System/Vector2.hpp>

class BodyRectangle : public sf::RectangleShape
{
public:
    BodyRectangle();
    BodyRectangle(sf::Vector2f pos);

    inline void moveRight(std::uint16_t distance = 1)
    {
        setPosition({getPosition().x + distance * g_unitX, getPosition().y});
    }
    inline void moveLeft(std::uint16_t distance = 1)
    {
        setPosition({getPosition().x - distance * g_unitX, getPosition().y});
    }
    inline void moveUp(std::uint16_t distance = 1)
    {
        setPosition({getPosition().x, getPosition().y - distance * g_unitY});
    }
    inline void moveDown(std::uint16_t distance = 1)
    {
        setPosition({getPosition().x, getPosition().y + distance * g_unitY});
    }
};

#endif // BODYRECTANGLE_H
