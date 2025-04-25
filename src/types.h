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

struct Vector3 {
    float x;
    float y;
    float z;
};

struct Vector2 {
    float x;
    float y;
};

struct Camera {
    Position pos;
    float FOV;
    float NEAR_PLANE;

    Camera(Position pos = Position(0, 0, 0, Rotation(0, 0, 0)), float fov = 600.f, float near_plane = 3.0f)
        : pos(pos), FOV(fov), NEAR_PLANE(near_plane) {}
};



#endif //TYPES_H
