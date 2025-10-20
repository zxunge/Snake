// SPDX-License-Identifier: MIT

#include "foodrectangle.h"
#include "snakebody.h"

#include <SFML/Graphics.hpp>

#include <chrono>
#include <optional>
#include <random>
#include <string>

std::mt19937 g_randGen;

int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode({70 * g_unitX, 65 * g_unitY}), "Snake", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    // Initialization
    g_randGen                                = std::mt19937(std::random_device{}());
    std::chrono::milliseconds movingInterval = g_defMovingInterval;

    // Load fonts
    sf::Font font;
    if (!font.openFromFile(g_fontFile))
        return -1;
    sf::Text text(font); // Global text holder
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    SnakeBody              snake(window.getSize());
    FoodRectangle          foodRect(window.getSize());
    Direction              movingDirection   = Direction::Down;
    auto                   begin             = std::chrono::high_resolution_clock::now();
    auto                   lastOperationTime = begin;
    bool                   failed = false, welcome = true, noChecks = false;
    sf::Keyboard::Scancode lastKey = sf::Keyboard::Scancode::Unknown;

    while (window.isOpen())
    {
        // Handle events
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (lastKey == keyPressed->scancode && movingInterval.count() >= std::chrono::milliseconds(30).count())
                    movingInterval -= std::chrono::milliseconds(5);
                switch (keyPressed->scancode)
                {
                    case sf::Keyboard::Scancode::Up:
                    case sf::Keyboard::Scancode::W:
                        movingDirection = Direction::Up;
                        snake.move(movingDirection);
                        break;

                    case sf::Keyboard::Scancode::Down:
                    case sf::Keyboard::Scancode::S:
                        movingDirection = Direction::Down;
                        snake.move(movingDirection);
                        break;

                    case sf::Keyboard::Scancode::Left:
                    case sf::Keyboard::Scancode::A:
                        movingDirection = Direction::Left;
                        snake.move(movingDirection);
                        break;

                    case sf::Keyboard::Scancode::Right:
                    case sf::Keyboard::Scancode::D:
                        movingDirection = Direction::Right;
                        snake.move(movingDirection);
                        break;

                    case sf::Keyboard::Scancode::Space:
                        welcome = false;
                        break;

                    case sf::Keyboard::Scancode::M:
                        // Interesting feature
                        noChecks = true;
                        break;

                    case sf::Keyboard::Scancode::N:
                        // Interesting feature
                        noChecks = false;
                        break;

                    case sf::Keyboard::Scancode::R:
                        // Recover default moving interval
                        movingInterval = g_defMovingInterval;
                        break;

                    case sf::Keyboard::Scancode::Enter:
                        if (failed)
                        {
                            // Reset variables
                            snake             = SnakeBody(window.getSize());
                            foodRect          = FoodRectangle(window.getSize());
                            movingDirection   = Direction::Down;
                            begin             = std::chrono::high_resolution_clock::now();
                            lastOperationTime = begin;
                            failed            = false;
                            movingInterval    = g_defMovingInterval;
                        }
                        break;

                    default:
                        break;
                }
                lastKey = keyPressed->scancode;
                break;
            }
        }

        // Clear window
        window.clear(sf::Color(0, 0, 0, 255));

        // Draw graphic items
        if (!welcome && !failed) [[likely]]
        {
            auto now     = std::chrono::high_resolution_clock::now();
            auto elapsed = now - lastOperationTime;
            if (elapsed >= movingInterval)
            {
                snake.move(movingDirection);
                lastOperationTime = now;
            }

            if (snake.intersects(foodRect))
            {
                snake.eat(foodRect);
                foodRect.updatePos();
            }

            if (!noChecks && !snake.isValid())
                failed = true;

            snake.render(window);
            window.draw(foodRect);
            window.setTitle("Snake: Scores - " + std::to_string(snake.score()));
        }
        else if (!welcome && failed)
        {
            text.setPosition({0.0f, static_cast<float>(window.getSize().y / 2)});
            text.setString(sf::String("You are failed. Press <Enter> to restart the game."));
            window.draw(text);
        }
        else
        {
            // Render a Welcome window
            text.setPosition({0.0f, static_cast<float>(window.getSize().y / 2)});
            text.setString(sf::String("Welcome to the Snake Game developed by zxunge! Start by pressing <Space>."));
            window.draw(text);
        }

        // Update window
        window.display();
    }

    return 0;
}
