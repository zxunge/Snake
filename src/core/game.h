// SPDX-License-Identifier: MIT

#ifndef GAME_H
#define GAME_H

#include "snakebody.h"

#include <SFML/Graphics.hpp>

namespace game
{
/*
GameController is the central interface of the game.
This class will monitor the working of game:
*	Movement of snake
*	Checking the validity of the snake
*/

const std::string MenuStrings[5] = {"Game Over!", "Do you wish to continue?", "Yes", "No", "Exit"}; // menu strings

enum MenuText
{
    GameOver,
    Continue,
    Yes,
    No,
    Exit,
}; // menuText

enum Fonts
{
};

/*==================================================*
 *			The main game controller
 *==================================================*/
class GameController
{
public:
    /* Constructors */
    GameController(sf::RenderWindow* w);

    /* Public methods */
    void start();
    /* methods to access the resources */
    sf::Font* getFont(Fonts font); // no definition yet

private:
    void gameLoop();
    void setupScene();
    void gameOver();      // no definition yet
    void loadResources(); // no definition yet

    SnakeBody         m_snake;
    sf::RenderWindow* m_screen;
    float             m_scale;
    int               m_score;

    /* Resources that the controller retrieves from Disk */
    sf::Font m_fontList[3];

}; // class game

} // namespace game

#endif // GAME_H
