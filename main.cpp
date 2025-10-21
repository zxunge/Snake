// SPDX-License-Identifier: MIT

// clang-format off
#include <SFML/Graphics.hpp>

#include <optional>
#include <random>
#include <string>

#include "callbacklongpressdetector.h"
#include "foodrectangle.h"
#include "snakebody.h"
// clang-format on

std::default_random_engine g_randGen;

int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode({60 * g_unitX, 50 * g_unitY}), "Snake", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    // Initialization
    g_randGen                = std::default_random_engine(static_cast<unsigned>(time(nullptr)));
    sf::Time  movingInterval = g_defMovingInterval;
    sf::Clock clock;

    // Load fonts
    sf::Font font;
    if (!font.openFromFile(g_fontFile))
        return -1;
    sf::Text text(font); // Global text holder
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    SnakeBody     snake(window.getSize());
    FoodRectangle foodRect(window.getSize());
    Direction     movingDirection = Direction::Down;
    bool          failed = false, welcome = true, noChecks = false;

    // Key handlers
    CallbackLongPressDetector detectorW(sf::Keyboard::Scancode::W, 0.5f);
    CallbackLongPressDetector detectorA(sf::Keyboard::Scancode::A, 0.5f);
    CallbackLongPressDetector detectorS(sf::Keyboard::Scancode::S, 0.5f);
    CallbackLongPressDetector detectorD(sf::Keyboard::Scancode::D, 0.5f);
    CallbackLongPressDetector detectorUp(sf::Keyboard::Scancode::Up, 0.5f);
    CallbackLongPressDetector detectorDown(sf::Keyboard::Scancode::Down, 0.5f);
    CallbackLongPressDetector detectorLeft(sf::Keyboard::Scancode::Left, 0.5f);
    CallbackLongPressDetector detectorRight(sf::Keyboard::Scancode::Right, 0.5f);

    detectorA.setCallbacks(
        [&]()
        {
            movingDirection = Direction::Left;
            snake.move(movingDirection);
        },
        [&]()
        {
            if (movingInterval >= sf::milliseconds(30))
                movingInterval -= sf::milliseconds(5);
        },
        [&]()
        {
            // Recover default moving interval
            movingInterval = g_defMovingInterval;
        },
        [&]() {});
    detectorLeft.setCallbacks(
        [&]()
        {
            movingDirection = Direction::Left;
            snake.move(movingDirection);
        },
        [&]()
        {
            if (movingInterval >= sf::milliseconds(30))
                movingInterval -= sf::milliseconds(5);
        },
        [&]()
        {
            // Recover default moving interval
            movingInterval = g_defMovingInterval;
        },
        [&]() {});
    detectorW.setCallbacks(
        [&]()
        {
            movingDirection = Direction::Up;
            snake.move(movingDirection);
        },
        [&]()
        {
            if (movingInterval >= sf::milliseconds(30))
                movingInterval -= sf::milliseconds(5);
        },
        [&]()
        {
            // Recover default moving interval
            movingInterval = g_defMovingInterval;
        },
        [&]() {});
    detectorUp.setCallbacks(
        [&]()
        {
            movingDirection = Direction::Up;
            snake.move(movingDirection);
        },
        [&]()
        {
            if (movingInterval >= sf::milliseconds(30))
                movingInterval -= sf::milliseconds(5);
        },
        [&]()
        {
            // Recover default moving interval
            movingInterval = g_defMovingInterval;
        },
        [&]() {});
    detectorS.setCallbacks(
        [&]()
        {
            movingDirection = Direction::Down;
            snake.move(movingDirection);
        },
        [&]()
        {
            if (movingInterval >= sf::milliseconds(30))
                movingInterval -= sf::milliseconds(5);
        },
        [&]()
        {
            // Recover default moving interval
            movingInterval = g_defMovingInterval;
        },
        [&]() {});
    detectorDown.setCallbacks(
        [&]()
        {
            movingDirection = Direction::Down;
            snake.move(movingDirection);
        },
        [&]()
        {
            if (movingInterval >= sf::milliseconds(30))
                movingInterval -= sf::milliseconds(5);
        },
        [&]()
        {
            // Recover default moving interval
            movingInterval = g_defMovingInterval;
        },
        [&]() {});
    detectorD.setCallbacks(
        [&]()
        {
            movingDirection = Direction::Right;
            snake.move(movingDirection);
        },
        [&]()
        {
            if (movingInterval >= sf::milliseconds(30))
                movingInterval -= sf::milliseconds(5);
        },
        [&]()
        {
            // Recover default moving interval
            movingInterval = g_defMovingInterval;
        },
        [&]() {});
    detectorRight.setCallbacks(
        [&]()
        {
            movingDirection = Direction::Right;
            snake.move(movingDirection);
        },
        [&]()
        {
            if (movingInterval >= sf::milliseconds(30))
                movingInterval -= sf::milliseconds(5);
        },
        [&]()
        {
            // Recover default moving interval
            movingInterval = g_defMovingInterval;
        },
        [&]() {});

    while (window.isOpen())
    {
        // Handle events
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                switch (keyPressed->scancode)
                {
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

                    case sf::Keyboard::Scancode::U:
                        foodRect.updatePos();
                        break;

                    case sf::Keyboard::Scancode::Enter:
                        if (failed)
                        {
                            // Reset variables
                            snake           = SnakeBody(window.getSize());
                            foodRect        = FoodRectangle(window.getSize());
                            movingDirection = Direction::Down;
                            failed          = false;
                            movingInterval  = g_defMovingInterval;
                        }
                        break;

                    default:
                        break;
                }
                break;
            }
        }
        detectorW.update();
        detectorA.update();
        detectorS.update();
        detectorD.update();
        detectorUp.update();
        detectorRight.update();
        detectorDown.update();
        detectorLeft.update();

        // Clear window
        window.clear(sf::Color(0, 0, 0, 255));

        // Draw graphic items
        if (!welcome && !failed) [[likely]]
        {
            if (clock.getElapsedTime() >= movingInterval)
            {
                snake.move(movingDirection);
                clock.restart();
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
