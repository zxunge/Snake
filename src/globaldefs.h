// SPDX-License-Identifier: MIT

#ifndef GLOBALDEFS_H
#define GLOBALDEFS_H

#include <SFML/Graphics/Color.hpp>

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include <filesystem>
#include <random>

const int                         g_unitX         = 15;
const int                         g_unitY         = 15;
const int                         g_initialLength = 3;
const sf::Color                   g_bodyColor     = sf::Color::Green;
const sf::Color                   g_foodColor     = sf::Color::Red;
const std::filesystem::path       g_fontFile("sansation.ttf");
const sf::Time                    g_defMovingInterval = sf::milliseconds(80);
extern std::default_random_engine g_randGen;
extern std::filesystem::path      g_exeDir;

enum class Direction
{
    Left,
    Right,
    Up,
    Down
};

#endif // GLOBALDEFS_H
