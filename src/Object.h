//
// Created by CJ on 4/23/2025.
//

#ifndef OBJECT_H
#define OBJECT_H

#include "includes.h"
#include "types.h"
#include "Point.h"

/**
 * Class defining a 3D object
 */
class Object {
public:

    Object(const std::vector<Point> &points, Vector3 pos, sf::RenderWindow& window);

    void draw();
    void move(Vector3 pos);

    Object& operator=(const Object& other);


private:
    Position _pos{};
    std::vector<Point> _points;
    sf::RenderWindow* _window;
};



#endif //OBJECT_H
