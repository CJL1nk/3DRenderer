//
// Created by cj_link on 4/25/25.
//

#include "Hitbox.h"

/**
 * Constructor, takes in a type and dimensions
 * @param type Hitbox type, unimplemented currently
 * @param x X dimension
 * @param y Y dimension
 * @param z Z dimension
 */
Hitbox::Hitbox(const HitboxType type, const float x, const float y, const float z) {
    _type = type;
    _x = x;
    _y = y;
    _z = z;
}

/**
 * For initializing a custom hitbox, currently unimplemented
 * @param points points of custom hitbox
 */
void Hitbox::init(const std::vector<Point> &points) {
    _points = points;
}

/**
 * Returns hitbox's X dimension
 * @return Hitbox's X dimension
 */
float Hitbox::getX() const {
    return this->_x;
}

/**
 * Returns hitbox's Y dimension
 * @return Hitbox's Y dimension
 */
float Hitbox::getY() const {
    return this->_y;
}

/**
 * Returns hitbox's Z dimension
 * @return Hitbox's Z dimension
 */
float Hitbox::getZ() const {
    return this->_z;
}