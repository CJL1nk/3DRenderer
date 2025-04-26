//
// Created by CJ on 4/23/2025.
//

#ifndef TYPES_H
#define TYPES_H

struct Rotation {
    float pitch;
    float roll;
    float yaw;
};

struct Position {
    float x;
    float y;
    float z;

    Rotation rotation;
};

struct Camera {
    Position pos;
    float FOV;
    float NEAR_PLANE;

    explicit Camera(const Position &pos = Position(0, 0, 0, Rotation(0, 0, 0)), const float fov = 600.f, const float near_plane = 3.0f)
        : pos(pos), FOV(fov), NEAR_PLANE(near_plane) {}
};

inline Camera camera = Camera(); // This is defined here because I want to

#endif //TYPES_H
