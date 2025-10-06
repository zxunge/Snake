// SPDX-License-Identifier: MIT

#ifndef GLOBALDEFS_H
#define GLOBALDEFS_H

#include <SFML/Graphics/Color.hpp>

#include <chrono>
#include <string>

const int                       g_unitX         = 20;
const int                       g_unitY         = 20;
const int                       g_initialLength = 3;
const sf::Color                 g_bodyColor     = sf::Color::Green;
const sf::Color                 g_foodColor     = sf::Color::Red;
const std::chrono::milliseconds g_movingInterval(80);
const std::string               g_fontFile("Zxunge Hand-Regular.ttf");

enum class Direction
{
    Left,
    Right,
    Up,
    Down
};

#endif // GLOBALDEFS_H
