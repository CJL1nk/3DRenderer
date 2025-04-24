//
// Created by CJ on 4/23/2025.
//

#ifndef OBJECT_H
#define OBJECT_H

#include "includes.h"
#include "types.h"
#include "Point.h"

class Object {
public:

    Object(std::vector<Point>& points, Vector3 pos, sf::RenderWindow& window);

    void draw();
    void move(sf::Vector2f pos);

    Object& operator=(const Object& other);


private:
    Position _pos;
    std::vector<Point> _points;
    sf::RenderWindow* _window;
};



#endif //OBJECT_H
