//
// Created by CJ on 4/23/2025.
//

#ifndef OBJECT_H
#define OBJECT_H

#include "includes.h"

class Object {
public:

    Object(sf::VertexArray points, sf::Vector2f pos, sf::RenderWindow& window);

    void draw();
    void move(sf::Vector2f pos);

    Object& operator=(const Object& other);

private:
    Position _pos;
    sf::VertexArray _points;
    sf::RenderWindow* _window;
};



#endif //OBJECT_H
