// SPDX-License-Identifier: MIT

#ifndef FOODRECTANGLE_H
#define FOODRECTANGLE_H

#include "bodyrectangle.h"
#include "globaldefs.h"

#include <cstdlib>

class FoodRectangle : public BodyRectangle
{
public:
    FoodRectangle(sf::Vector2u windowSize) : BodyRectangle(), m_windowSize(windowSize)
    {
        setFillColor(g_foodColor);
        setSize(sf::Vector2f(g_unitX, g_unitY));
    }

    void updatePos()
    {
        setPosition((g_randGen() % (static_cast<int>(m_windowSize.x) / g_unitX)) * g_unitX,
                    (g_randGen() % (static_cast<int>(m_windowSize.y) / g_unitY)) * g_unitY);
    }

private:
    sf::Vector2u m_windowSize;
};

#endif // FOODRECTANGLE_H
