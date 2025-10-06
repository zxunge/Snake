#include "bodyrectangle.h"

using namespace sf;

BodyRectangle::BodyRectangle()
{
    setFillColor(g_bodyColor);
    setSize(Vector2f(g_unitX, g_unitY));
    setPosition(0.0, 0.0);
}

BodyRectangle::BodyRectangle(sf::Vector2f pos)
{
    setFillColor(g_bodyColor);
    setSize(Vector2f(g_unitX, g_unitY));
    setPosition(pos.x * g_unitX, pos.y * g_unitY);
}
