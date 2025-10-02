#include "foodrectangle.h"
#include "snakebody.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>

using namespace sf;

int main(int argc, char *argv[])
{
    RenderWindow window(VideoMode(800, 600), "Snake");
    window.setFramerateLimit(60);

    // Initialize random value generator
    std::time_t t;
    std::srand(static_cast<unsigned>(time(&t)));

    SnakeBody snake;

    while(window.isOpen()) {
        // Handle events
        Event event;
        while(window.pollEvent(event))
            switch (event.type) {
            case Event::EventType::Closed:
                window.close();
                break;

            default:
                break;
            }

        // Clear window
        window.clear(Color(0, 0, 0, 255));

        // Draw graphic items

        // Update window
        window.display();
    }

    return 0;
}
