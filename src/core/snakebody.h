// SPDX-License-Identifier: MIT

#ifndef SNAKEBODY_H
#define SNAKEBODY_H

#include "bodyrectangle.h"
#include "foodrectangle.h"
#include "globaldefs.h"

#include <SFML/Graphics.hpp>

#include <optional>
#include <vector>

class SnakeBody
{
public:
    SnakeBody(sf::Vector2u windowSize) : m_windowSize(windowSize)
    {
        // Initially, we have `g_initialLength' rectangles on the top.
        for (float i = g_initialLength - 1; i >= 0; --i)
            m_body.push_back(BodyRectangle({0.0f, i}));
    }

    void move(Direction direction);
    void eat(FoodRectangle food);
    void render(sf::RenderWindow* wnd)
    {
        for (auto r : m_body)
            wnd->draw(r);
    }
    bool intersects(sf::RectangleShape rect)
    {
        if (m_body[0].getGlobalBounds().findIntersection(rect.getGlobalBounds()) != std::nullopt)
            return true;
        return false;
    }
    bool isValid()
    {
        for (auto r : m_body)
            if (r.getPosition().x < 0 || r.getPosition().x > m_windowSize.x || r.getPosition().y < 0 ||
                r.getPosition().y > m_windowSize.y)
                return false;
        return true;
    }
    std::uint32_t score()
    {
        return m_body.size() - g_initialLength;
    }

private:
    std::vector<BodyRectangle> m_body;
    sf::Vector2u               m_windowSize;
};

#endif // SNAKEBODY_H
