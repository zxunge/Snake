#ifndef SNAKEBODY_H
#define SNAKEBODY_H

#include "bodyrectangle.h"
#include "globaldefs.h"
#include <SFML/Graphics.hpp>
#include <vector>

class SnakeBody : public sf::VertexArray
{
public:
    SnakeBody();

    void move(Direction direction);

private:
    std::vector<BodyRectangle> m_body;
};

#endif // SNAKEBODY_H
