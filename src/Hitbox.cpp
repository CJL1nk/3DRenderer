//
// Created by cj_link on 4/25/25.
//

#include "Hitbox.h"

Hitbox::Hitbox(const HitboxType type) {

    _type = type;

    switch (type) {
        case HitboxType::CUBE:
            _radius = 1.f;
            _x = 1.f;
            _y = 1.f;
            _z = 1.f;
            break;
        case HitboxType::RECTANGLE_PRISM:
            _x = 1.f;
            _y = 1.f;
            _z = 2.f;
        break;
        case HitboxType::SPHERE:
            _radius = 1.f;
            break;
        case HitboxType::CUSTOM:
            // Will create default point vector soon LOL
            _points = std::vector<Point>({Point("1", Vector3(-1.5f, -1.5f, -1.5f), std::vector<std::string>{"2", "4", "5"}),
                                            Point("2", Vector3( 1.5f, -1.5f, -1.5f), std::vector<std::string>{"3", "6"}),
                                            Point("3", Vector3( 1.5f,  1.5f, -1.5f), std::vector<std::string>{"4", "7"}),
                                            Point("4", Vector3(-1.5f,  1.5f, -1.5f), std::vector<std::string>{"1", "8"}),
                                            Point("5", Vector3(-1.5f, -1.5f,  1.5f), std::vector<std::string>{"6", "8"}),
                                            Point("6", Vector3( 1.5f, -1.5f,  1.5f), std::vector<std::string>{"7"}),
                                            Point("7", Vector3( 1.5f,  1.5f,  1.5f), std::vector<std::string>{"8"}),
                                            Point("8", Vector3(-1.5f,  1.5f,  1.5f))});
    }
}

void Hitbox::init(const float radius) {
    _radius = radius;
}

void Hitbox::init(const float x, const float y, const float z) {
    _x = x;
    _y = y;
    _z = z;
}

void Hitbox::init(const std::vector<Point> &points) {
    _points = points;
}

float Hitbox::getRadius() const {
    return this->_radius;
}