// SPDX-License-Identifier: MIT

#include "globaldefs.h"
#include "ui/mainmenu.h"

#include <SFML/Window.hpp>

std::default_random_engine g_randGen;

int main(int argc, char** argv)
{
    sf::RenderWindow window(sf::VideoMode({50 * g_unitX, 50 * g_unitY}), "Snake", sf::Style::Close);
    game::MainMenu   menu(window);
    // Initialization
    g_randGen = std::default_random_engine(std::random_device{}());
    menu.start();
    return 0;
}
