//
// Created by CJ on 4/23/2025.
//

#include "Object.h"


Object::Object(sf::VertexArray points, sf::Vector2f pos, sf::RenderWindow& window) {

    this->_pos = Position(pos.x, pos.y);
    this->_points = points;
    this->_window = &window;
}

void Object::draw() {

    sf::VertexArray points = _points;

    for (int i = 0; i < points.getVertexCount(); i++) {
        points[i].position.x += _pos.x;
        points[i].position.y += _pos.y;
    }


    _window->draw(points);
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