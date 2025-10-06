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

    inline void moveRight(sf::Uint16 distance = 1)
    {
        setPosition(getPosition().x + distance * g_unitX, getPosition().y);
    }
    inline void moveLeft(sf::Uint16 distance = 1)
    {
        setPosition(getPosition().x - distance * g_unitX, getPosition().y);
    }
    inline void moveUp(sf::Uint16 distance = 1)
    {
        setPosition(getPosition().x, getPosition().y - distance * g_unitY);
    }
    inline void moveDown(sf::Uint16 distance = 1)
    {
        setPosition(getPosition().x, getPosition().y + distance * g_unitY);
    }
};

#endif // BODYRECTANGLE_H
