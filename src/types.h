//
// Created by CJ on 4/23/2025.
//

#ifndef TYPES_H
#define TYPES_H

struct Rotation {
    double pitch;
    double roll;
    double yaw;
};

struct Position {
    double x;
    double y;
    double z;

    Rotation rotation;
};

#endif //TYPES_H
