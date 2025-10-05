#include "foodrectangle.h"
#include "snakebody.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>

using namespace sf;

int main(int argc, char *argv[]) {
  RenderWindow window(VideoMode(810, 600), "Snake",
                      sf::Style::Titlebar | sf::Style::Close);
  window.setFramerateLimit(30);

  // Initialize random value generator
  std::time_t t;
  std::srand(static_cast<unsigned>(time(&t)));

  SnakeBody snake;
  FoodRectangle foodRect(window.getSize());

  while (window.isOpen()) {
    // Handle events
    Event event;
    while (window.pollEvent(event))
      switch (event.type) {
      case sf::Event::EventType::Closed:
        window.close();
        break;

      case sf::Event::EventType::KeyPressed:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
          snake.move(Direction::Up);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
          snake.move(Direction::Down);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
          snake.move(Direction::Left);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
          snake.move(Direction::Right);
        break;

      default:
        break;
      }

    // Clear window
    window.clear(Color(0, 0, 0, 255));

    // Draw graphic items
    if (snake.intersects(foodRect))
      foodRect.updatePos();
    snake.render(window);
    window.draw(foodRect);

    // Update window
    window.display();
  }

  return 0;
}
