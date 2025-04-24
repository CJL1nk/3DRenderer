//
// Created by CJ on 4/23/2025.
//

#include "Object.h"

Object::Object(std::vector<Point> points, Vector3 pos, sf::RenderWindow& window) {

    this->_pos = Position(pos.x, pos.y, pos.z);
    this->_points = std::move(points);
    this->_window = &window;
}

void Object::draw() {

    for (Point point : this->_points) {
        std::cout << point.label() << " Connections:" << std::endl;
        for (auto& connection : point.connections()) {
            std::cout << " " << connection.first << std::endl;
        }
    }
}


void Object::move(sf::Vector2f pos) {
    _pos.x = pos.x;
    _pos.y = pos.y;
}

Object& Object::operator=(const Object& other) {
    this->_pos = other._pos;
    this->_points = other._points;
    this->_window = other._window;
    return *this;
}