// SPDX-License-Identifier: MIT

#include "snakebody.h"

void SnakeBody::move(Direction direction)
{
    for (int i = m_body.size() - 1; i != 0; --i)
        m_body[i].setPosition(m_body[i - 1].getPosition().x, m_body[i - 1].getPosition().y);
    switch (direction)
    {
        case Direction::Left:
            m_body[0].moveLeft();
            break;

        case Direction::Right:
            m_body[0].moveRight();
            break;

        case Direction::Up:
            m_body[0].moveUp();
            break;

        case Direction::Down:
            m_body[0].moveDown();
            break;
    }
}

void SnakeBody::eat(FoodRectangle food)
{
    // We must let m_body[0] be the `food'
    m_body.resize(m_body.size() + 1);
    for (long i = m_body.size() - 2; i >= 0; --i)
        m_body[i + 1] = m_body[i];
    m_body[0] = food;
    m_body[0].setFillColor(g_bodyColor); // Restore the color.
}
