// SPDX-License-Identifier: MIT

#include "foodrectangle.h"
#include "snakebody.h"

#include <SFML/Graphics.hpp>

#include <chrono>
#include <string>

#include <cstdlib>
#include <random>

using namespace sf;

std::mt19937 g_randGen;

int main(int argc, char* argv[])
{
    RenderWindow window(VideoMode(25 * g_unitX, 20 * g_unitY), "Snake", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    // Initialize random value generator
    std::random_device rd;
    g_randGen = std::mt19937(rd());

    // Load fonts
    Font font;
    if (!font.loadFromFile(g_fontFile))
        return -1;
    sf::Text text; // Global text holder
    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    SnakeBody     snake(window.getSize());
    FoodRectangle foodRect(window.getSize());
    Direction     movingDirection   = Direction::Down;
    auto          begin             = std::chrono::high_resolution_clock::now();
    auto          lastOperationTime = begin;
    bool          failed = false, welcome = true;

    while (window.isOpen())
    {
        // Handle events
        Event event;
        while (window.pollEvent(event))
            switch (event.type)
            {
                case sf::Event::EventType::Closed:
                    window.close();
                    break;

                case sf::Event::EventType::KeyPressed:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) ||
                        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
                    {
                        movingDirection = Direction::Up;
                        snake.move(movingDirection);
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) ||
                             sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
                    {
                        movingDirection = Direction::Down;
                        snake.move(movingDirection);
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ||
                             sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
                    {
                        movingDirection = Direction::Left;
                        snake.move(movingDirection);
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) ||
                             sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
                    {
                        movingDirection = Direction::Right;
                        snake.move(movingDirection);
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
                        welcome = false;
                    else if (failed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
                    {
                        // Reset variables
                        snake             = SnakeBody(window.getSize());
                        foodRect          = FoodRectangle(window.getSize());
                        movingDirection   = Direction::Down;
                        begin             = std::chrono::high_resolution_clock::now();
                        lastOperationTime = begin;
                        failed            = false;
                    }
                    break;

                default:
                    break;
            }

        // Clear window
        window.clear(Color(0, 0, 0, 255));

        // Draw graphic items
        if (!welcome && !failed) [[likely]]
        {
            auto now     = std::chrono::high_resolution_clock::now();
            auto elapsed = now - lastOperationTime;
            if (elapsed >= g_movingInterval)
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
