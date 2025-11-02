// SPDX-License-Identifier: MIT

#include "game.h"

#include "foodrectangle.h"

namespace game
{

// constructor
GameController::GameController(sf::RenderWindow* w) : m_snake(w->getSize())
{
    m_screen = w;
    m_score  = 0;
}

void GameController::start()
{
    loadResources();
    // TODO
    gameLoop();
}

void GameController::gameLoop()
{
    bool      loopInvarient = true;
    Direction direction;
    m_scale = 5;
    FoodRectangle food(m_screen->getSize());
    while (loopInvarient)
    {
        setupScene();
        m_screen->draw(food);
        while (const std::optional event = m_screen->pollEvent())
        {
            if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
            {
                if (keyReleased->scancode == sf::Keyboard::Scancode::Up)
                {
                    direction = Direction::Up;
                }
                else if (keyReleased->scancode == sf::Keyboard::Scancode::Down)
                {
                    direction = Direction::Down;
                }
                else if (keyReleased->scancode == sf::Keyboard::Scancode::Left)
                {
                    direction = Direction::Left;
                }
                else if (keyReleased->scancode == sf::Keyboard::Scancode::Right)
                {
                    direction = Direction::Right;
                }
            }
            if (event->is<sf::Event::Closed>())
            {
                exit(0);
            }
        } // event loop
        m_snake.move(direction);
        if (!m_snake.isValid())
        {
            // game over
            loopInvarient = false;
        }
        if (m_snake.intersects(food))
        {
            m_snake.eat(food);
            m_score++;
            food.updatePos();
        }
        m_screen->display();
        m_screen->setFramerateLimit(60);
    }
} // gameLoop()

void GameController::setupScene()
{
    m_screen->clear();
    m_snake.render(m_screen);
}

bool checkCollision(const sf::RectangleShape& a, const sf::RectangleShape& b)
{
    return a.getGlobalBounds().findIntersection(b.getGlobalBounds()) != std::nullopt;
}

sf::RectangleShape getRectangleAt(sf::Vector2f location, sf::Color color)
{
    sf::RectangleShape box;
    box.setSize(sf::Vector2f(BOX_SIZE, BOX_SIZE));
    box.setPosition(location);
    box.setFillColor(color);
    return box;
}
void GameController::loadResources()
{
    // TODO
}
sf::Font* GameController::getFont(Fonts font)
{
    return &m_fontList[font];
}

} // namespace game
