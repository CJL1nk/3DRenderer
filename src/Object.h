//
// Created by CJ on 4/23/2025.
//

#ifndef OBJECT_H
#define OBJECT_H

#include "includes.h"
#include "types.h"
#include "Point.h"

float degreesToRadians(float degrees);

/**
 * Class defining a 3D object
 */
class Object {
public:

    Object(const std::vector<Point> &points, Vector3* pos, sf::RenderWindow& window);
    Object(const std::vector<Point> &points, Position* pos, sf::RenderWindow& window);

    void draw(const Camera& camera);
    void move(const Position pos);
    void setColor(const sf::Color& color = sf::Color::White);

    Object& operator=(const Object& other);


private:
    Position* _pos{};
    std::vector<Point> _points;
    sf::RenderWindow* _window;
    sf::Color _color;
};



#endif //OBJECT_H
