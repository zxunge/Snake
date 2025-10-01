#include "bodyrectangle.h"

using namespace sf;

BodyRectangle::BodyRectangle()
{
    setFillColor(Color::Green);
    setSize(Vector2f(unitX, unitY));
    setPosition(0.0, 0.0);
}

BodyRectangle::BodyRectangle(sf::Vector2f pos)
{
    setFillColor(Color::Green);
    setSize(Vector2f(unitX, unitY));
    setPosition(pos.x * unitX, pos.y * unitY);
}
