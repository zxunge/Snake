#ifndef SNAKEBODY_H
#define SNAKEBODY_H

#include "bodyrectangle.h"
#include "globaldefs.h"
#include <SFML/Graphics.hpp>
#include <vector>

class SnakeBody {
public:
  SnakeBody();

  void move(Direction direction);
  void render(sf::RenderWindow &wnd);
  bool intersects(sf::RectangleShape rect) {
    for (auto r : m_body)
      if (r.getGlobalBounds().intersects(rect.getGlobalBounds()))
        return true;
    return false;
  }

private:
  std::vector<BodyRectangle> m_body;
};

#endif // SNAKEBODY_H
