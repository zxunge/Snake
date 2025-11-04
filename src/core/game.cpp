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
    bool          loop = true, check = true;
    Direction     direction;
    FoodRectangle food(m_screen->getSize());
    m_scale = 5;
    while (loop)
    {
        setupScene();
        m_screen->draw(food);
        while (const std::optional event = m_screen->pollEvent())
        {
            if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
            {
                switch (keyReleased->scancode)
                {
                    case sf::Keyboard::Scancode::Up:
                    case sf::Keyboard::Scancode::W:
                        direction = Direction::Up;
                        break;
                    
                    case sf::Keyboard::Scancode::Down:
                    case sf::Keyboard::Scancode::S:
                        direction = Direction::Down;
                        break;
                    
                    case sf::Keyboard::Scancode::Left:
                    case sf::Keyboard::Scancode::A:
                        direction = Direction::Left;
                        break;
                    
                    case sf::Keyboard::Scancode::Right:
                    case sf::Keyboard::Scancode::D:
                        direction = Direction::Right;
                        break;

                    case sf::Keyboard::Scancode::U:
                        food.updatePos();
                        break;

                    case sf::Keyboard::Scancode::N:
                        check = false;
                        break;

                    case sf::Keyboard::Scancode::M:
                        check = true;
                        break;
                    
                    default:
                        break;
                }
            }
            if (event->is<sf::Event::Closed>())
                exit(EXIT_SUCCESS);
        } // event loop
        m_snake.move(direction);
        if (check && !m_snake.isValid()) // game over
            loop = false;
        if (m_snake.intersects(food))
        {
            m_snake.eat(food);
            ++m_score;
            food.updatePos();
        }
        m_screen->display();
        m_screen->setFramerateLimit(60);
    }
}

void GameController::setupScene()
{
    m_screen->clear();
    m_snake.render(m_screen);
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
