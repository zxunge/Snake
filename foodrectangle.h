#ifndef FOODRECTANGLE_H
#define FOODRECTANGLE_H

#include "globaldefs.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>

class FoodRectangle : public sf::RectangleShape {
public:
  FoodRectangle(sf::Vector2u windowSize) : m_windowSize(windowSize) {
    setFillColor(sf::Color::Red);
    setSize(sf::Vector2f(g_unitX, g_unitY));
  }

  void updatePos() {
    setPosition(
        (std::rand() % (static_cast<int>(m_windowSize.x) / g_unitX)) * g_unitX,
        (std::rand() % (static_cast<int>(m_windowSize.y) / g_unitY)) * g_unitY);
  }

private:
  sf::Vector2u m_windowSize;
};

#endif // FOODRECTANGLE_H
