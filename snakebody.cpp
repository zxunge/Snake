#include "snakebody.h"

SnakeBody::SnakeBody() {
  // Initially, we have `g_initialLength' rectangles on the top.
  for (int i = 0; i != g_initialLength; ++i)
    m_body.push_back(BodyRectangle(sf::Vector2f(0.0f, i)));
}

void SnakeBody::move(Direction direction) {
  for (int i = m_body.size() - 1; i != 0; --i) {
    m_body[i].setPosition(m_body[i - 1].getPosition().x,
                          m_body[i - 1].getPosition().y);
  }
  switch (direction) {
  case Direction::Left:
    m_body[0].moveLeft();
    break;

  case Direction::Right:
    m_body[0].moveRight();
    break;

  case Direction::Up:
    m_body[0].moveUp();
    break;

  case Direction::Down:
    m_body[0].moveDown();
    break;
  }
}

void SnakeBody::render(sf::RenderWindow &wnd) {
  for (auto r : m_body)
    wnd.draw(r);
}
