// SPDX-License-Identifier: MIT

#ifndef GLOBALDEFS_H
#define GLOBALDEFS_H

#include <SFML/Graphics/Color.hpp>

#include <chrono>
#include <string>
#include <random>

const int                              g_unitX         = 20;
const int                              g_unitY         = 20;
const int                              g_initialLength = 3;
inline const sf::Color                 g_bodyColor     = sf::Color::Green;
inline const sf::Color                 g_foodColor     = sf::Color::Red;
inline const std::chrono::milliseconds g_movingInterval(80);
inline const std::string               g_fontFile("Zxunge Hand-Regular.ttf");
extern const std::mt19937              g_randGen;

enum class Direction
{
    Left,
    Right,
    Up,
    Down
};

#endif // GLOBALDEFS_H
