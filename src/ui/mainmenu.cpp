// SPDX-License-Identifier: MIT

#include "mainmenu.h"

#include "core/game.h"
#include "globaldefs.h"

namespace game
{

MainMenu::MainMenu(sf::RenderWindow& w) : m_window(w), m_mainMenuContext(nullptr, menu_destroy_context)
{
    setup_menu_context();
}

void MainMenu::start()
{
    m_window.setFramerateLimit(60);
    while (m_window.isOpen())
    {
        if (m_isExitRequested)
        {
            m_window.close();
            break;
        }
        while (std::optional event = m_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                m_isExitRequested = true;
                break;
            }
            menu_handle_event(m_currentMenu, event);
        }
        m_window.clear();
        menu_render(m_currentMenu);
        m_window.display();
    }
}

void MainMenu::setup_menu_context()
{
    if (!m_font.openFromFile(g_exeDir / g_fontFile))
        return;
    game_menu::Style style{.TitleFont            = &m_font,
                           .ItemFont             = &m_font,
                           .TitleFontSize        = 36,
                           .ItemFontSize         = 24,
                           .MenuTitleScaleFactor = 1,
                           .MenuItemScaleFactor  = 1.5,
                           .colorScheme = {.titleColor = 0xFFFFFF, .itemColor = 0xFFFFFF, .selectedColor = 0xFF22F1},
                           .PaddingTitle =
                               {
                                   .top  = 100,
                                   .left = 0,
                               },
                           .PaddingItems =
                               {
                                   .top = 40,
                               },
                           .TitleAlign = game_menu::Align::Center,
                           .ItemAlign  = game_menu::Align::Center};

    std::vector<game_menu::MenuItem> items{{"New Game",
                                            [&](sf::RenderTarget& target)
                                            {
                                                game::GameController gameController(&m_window);
                                                gameController.start();
                                            }},
                                           {"Exit", [&](sf::RenderTarget& target) { this->m_isExitRequested = true; }}};

    game_menu::MenuConfig config{.title = "Snake", .items = items, .style = style};
    m_mainMenuContext.reset(create_menu_context(m_window, config));
    m_currentMenu = m_mainMenuContext.get();
}

} // namespace game
