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

#endif //TYPES_H
