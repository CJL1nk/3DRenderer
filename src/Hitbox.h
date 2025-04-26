//
// Created by cj_link on 4/25/25.
//

#ifndef HITBOX_H
#define HITBOX_H

#include "includes.h"
#include "Point.h"

/**
 * Class defining a hitbox object. Each hitbox knows its own dimensions and later on, type
 */
enum class HitboxType {
    DEFAULT,
    SPHERE,
    CUSTOM
};

class Hitbox {

public:
    Hitbox() :  Hitbox(HitboxType::DEFAULT, 1.f, 1.f, 1.f) {}
    explicit Hitbox(HitboxType type, float x, float y, float z);
    explicit Hitbox(float x, float y, float z) : Hitbox(HitboxType::DEFAULT, x, y, z) {}

    // Currently unimplemented, for custom hitboxes
    explicit Hitbox(const std::vector<Point> &points);
    void init(const std::vector<Point> &points);

    [[nodiscard]] float getX() const;
    [[nodiscard]] float getY() const;
    [[nodiscard]] float getZ() const;

private:
    HitboxType _type;
    float _x{}, _y{}, _z{};

    std::vector<Point> _points;
};

#endif //HITBOX_H
