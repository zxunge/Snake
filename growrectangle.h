#ifndef GROWRECTANGLE_H
#define GROWRECTANGLE_H

#include "globaldefs.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>

class GrowRectangle : public sf::RectangleShape
{
public:
    GrowRectangle(sf::Vector2u windowSize)
    {
        setFillColor(sf::Color::Red);
        setSize(sf::Vector2f(unitX, unitY));
        setPosition((std::rand() % (static_cast<int>(windowSize.x) / unitX)) * unitX,
                    (std::rand() % (static_cast<int>(windowSize.y) / unitY)) * unitY);
    }
};

#endif // GROWRECTANGLE_H
