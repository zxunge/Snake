// SPDX-License-Identifier: MIT

#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics.hpp>

#include <game_menu/game_menu.h>
#include <memory>

namespace game
{

class MainMenu
{
public:
    MainMenu(sf::RenderWindow& w);
    void start();

private:
    void setup_menu_context();

    sf::RenderWindow&                                                       m_window;
    sf::Font                                                                m_font;
    game_menu::MENU*                                                        m_currentMenu;
    std::unique_ptr<game_menu::MENU, std::function<void(game_menu::MENU*)>> m_mainMenuContext;
    bool                                                                    m_isExitRequested = false;
};

} // namespace game

#endif // MAINMENU_H
