// SPDX-License-Identifier: MIT

#include "foodrectangle.h"
#include "snakebody.h"

#include <SFML/Graphics.hpp>

#include <chrono>
#include <random>
#include <string>

std::mt19937 g_randGen;

int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(45 * g_unitX, 40 * g_unitY), "Snake", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    // Initialization
    g_randGen                                = std::mt19937(std::random_device{}());
    std::chrono::milliseconds movingInterval = g_defMovingInterval;

    // Load fonts
    sf::Font font;
    if (!font.loadFromFile(g_fontFile))
        return -1;
    sf::Text text; // Global text holder
    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    SnakeBody         snake(window.getSize());
    FoodRectangle     foodRect(window.getSize());
    Direction         movingDirection   = Direction::Down;
    auto              begin             = std::chrono::high_resolution_clock::now();
    auto              lastOperationTime = begin;
    bool              failed = false, welcome = true;
    sf::Keyboard::Key lastKey = sf::Keyboard::Key::Unknown;

    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
            switch (event.type)
            {
                case sf::Event::EventType::Closed:
                    window.close();
                    break;

                case sf::Event::EventType::KeyPressed:
                    if (lastKey == event.key.code && movingInterval.count() >= std::chrono::milliseconds(30).count())
                        movingInterval -= std::chrono::milliseconds(5);
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Key::Up:
                        case sf::Keyboard::Key::W:
                            movingDirection = Direction::Up;
                            snake.move(movingDirection);
                            break;

                        case sf::Keyboard::Key::Down:
                        case sf::Keyboard::Key::S:
                            movingDirection = Direction::Down;
                            snake.move(movingDirection);
                            break;

                        case sf::Keyboard::Key::Left:
                        case sf::Keyboard::Key::A:
                            movingDirection = Direction::Left;
                            snake.move(movingDirection);
                            break;

                        case sf::Keyboard::Key::Right:
                        case sf::Keyboard::Key::D:
                            movingDirection = Direction::Right;
                            snake.move(movingDirection);
                            break;

                        case sf::Keyboard::Key::Space:
                            welcome = false;
                            break;

                        case sf::Keyboard::Key::R:
                            // Recover default moving interval
                            movingInterval = g_defMovingInterval;
                            break;

                        case sf::Keyboard::Key::Enter:
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
                    lastKey = event.key.code;
                    break;

                default:
                    break;
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

            if (!snake.isValid())
                failed = true;

            snake.render(window);
            window.draw(foodRect);
            window.setTitle("Snake: Scores - " + std::to_string(snake.score()));
        }
        else if (!welcome && failed)
        {
            text.setPosition(sf::Vector2f(0, window.getSize().y / 2));
            text.setString(sf::String("You are failed. Press <Enter> to restart the game."));
            window.draw(text);
        }
        else
        {
            // Render a Welcome window
            text.setPosition(sf::Vector2f(0, window.getSize().y / 2));
            text.setString(sf::String("Welcome to the Snake Game developed by zxunge! Start by pressing <Space>."));
            window.draw(text);
        }

        // Update window
        window.display();
    }

    return 0;
}
