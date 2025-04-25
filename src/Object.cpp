//
// Created by CJ on 4/23/2025.
//

#include "Object.h"

/**
 * @param points Object vertices
 * @param pos Object center position
 * @param window Window to render in
 */
Object::Object(const std::vector<Point> &points, const Vector3 pos, sf::RenderWindow& window) {

    this->_pos = Position(pos.x, pos.y, pos.z);
    this->_points = points;
    this->_window = &window;
}

/**
 * Draws object on screen
 */
void Object::draw() {

    for (const Point& point : this->_points) {
        std::cout << point.label() << " Connections:";
        for (auto& connection : point.connections()) {
            std::cout << " " << connection.first << " ";
        }
        std::cout << std::endl;
    }
}

/**
 * Moves an object to a given position
 * @param pos Position to move object to
 */
void Object::move(const Vector3 pos) {
    _pos.x = pos.x;
    _pos.y = pos.y;
    _pos.z = pos.z;
}

Object& Object::operator=(const Object& other) = default;