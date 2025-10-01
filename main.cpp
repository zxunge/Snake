#include "bodyrectangle.h"
#include "growrectangle.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>

using namespace sf;

int main(int argc, char *argv[])
{
    RenderWindow window(VideoMode(800, 600), "Snake");
    window.setFramerateLimit(60);

    std::time_t t;
    // Initialize random value generator
    std::srand(static_cast<unsigned>(time(&t)));

    BodyRectangle rect;

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
        rect.moveRight(1);
        window.draw(rect);
        GrowRectangle rect2(window.getSize());
        window.draw(rect2);

        // Update window
        window.display();
    }

    return 0;
}
