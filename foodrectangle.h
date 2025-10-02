#ifndef FOODRECTANGLE_H
#define FOODRECTANGLE_H

#include "globaldefs.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>

class FoodRectangle : public sf::RectangleShape
{
public:
    FoodRectangle(sf::Vector2u windowSize)
    {
        setFillColor(sf::Color::Red);
        setSize(sf::Vector2f(g_unitX, g_unitY));
        setPosition((std::rand() % (static_cast<int>(windowSize.x) / g_unitX)) * g_unitX,
                    (std::rand() % (static_cast<int>(windowSize.y) / g_unitY)) * g_unitY);
    }
};

#endif // FOODRECTANGLE_H
