// SPDX-License-Identifier: MIT

#ifndef FOODRECTANGLE_H
#define FOODRECTANGLE_H

#include "bodyrectangle.h"
#include "globaldefs.h"

#include <random>

class FoodRectangle : public BodyRectangle
{
public:
    FoodRectangle(sf::Vector2u windowSize) : BodyRectangle(), m_windowSize(windowSize)
    {
        setFillColor(g_foodColor);
        setSize({g_unitX, g_unitY});
        updatePos();
    }

    void updatePos()
    {
        std::uniform_int_distribution<int> distribX(0, static_cast<int>(m_windowSize.x) / g_unitX - 1);
        std::uniform_int_distribution<int> distribY(0, static_cast<int>(m_windowSize.y) / g_unitY - 1);
        setPosition({static_cast<float>(distribX(g_randGen) * g_unitX), static_cast<float>(distribY(g_randGen) * g_unitY)});
    }

private:
    sf::Vector2u m_windowSize;
};

#endif // FOODRECTANGLE_H
