//
// Created by cj_link on 4/25/25.
//

#ifndef HITBOX_H
#define HITBOX_H

#include "includes.h"
#include "types.h"
#include "Point.h"

enum class HitboxType {
    CUBE,
    RECTANGLE_PRISM,
    SPHERE,
    CUSTOM
};

class Hitbox {

public:
    Hitbox() : _type(HitboxType::CUBE) {}
    explicit Hitbox(HitboxType type);

    void init(float radius = 1.f);
    void init(float x, float y, float z);
    void init(const std::vector<Point> &points);

    float getRadius() const;


private:
    HitboxType _type;

    float _radius{}; // Also used for cube side length
    float _x{}, _y{}, _z{};

    std::vector<Point> _points;
    Position _pos;
};



#endif //HITBOX_H
