// SPDX-License-Identifier: MIT

#include "globaldefs.h"
#include "ui/mainmenu.h"

#include <sfml/Window.hpp>

std::default_random_engine g_randGen;
std::filesystem::path g_exeDir;

int main(int argc, char** argv)
{
    sf::RenderWindow window(sf::VideoMode({50 * g_unitX, 50 * g_unitY}), "Snake", sf::Style::Close);
    game::MainMenu   menu(window);
    // Initialization
    g_randGen = std::default_random_engine(std::random_device{}());
    g_exeDir = std::filesystem::absolute(argv[0]).parent_path();
    menu.start();
    return 0;
}
