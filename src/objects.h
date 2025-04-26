//
// Created by CJ on 4/26/2025.
//

#ifndef OBJECTS_H
#define OBJECTS_H

#include "includes.h"
#include "Point.h"
#include "Hitbox.h"
#include "Object.h"

void initPlane();

inline std::vector<Point> tetrahedronPoints = {
    Point("A", sf::Vector3f(-10.0f, -3.0f, -5.78f), std::vector<std::string>{"B", "C", "D"}),
    Point("B", sf::Vector3f( 10.0f, -3.0f, -5.78f), std::vector<std::string>{"C", "D"}),
    Point("C", sf::Vector3f( 0.0f, -3.0f,  11.55f), std::vector<std::string>{"D"}),
    Point("D", sf::Vector3f( 0.0f,  -18.0f,  0.0f))
};


inline std::vector<Point> cubePoints = {
    Point("1", sf::Vector3f(-1.5f, -1.5f, -1.5f), std::vector<std::string>{"2", "4", "5"}),
    Point("2", sf::Vector3f( 1.5f, -1.5f, -1.5f), std::vector<std::string>{"3", "6"}),
    Point("3", sf::Vector3f( 1.5f,  1.5f, -1.5f), std::vector<std::string>{"4", "7"}),
    Point("4", sf::Vector3f(-1.5f,  1.5f, -1.5f), std::vector<std::string>{"1", "8"}),
    Point("5", sf::Vector3f(-1.5f, -1.5f,  1.5f), std::vector<std::string>{"6", "8"}),
    Point("6", sf::Vector3f( 1.5f, -1.5f,  1.5f), std::vector<std::string>{"7"}),
    Point("7", sf::Vector3f( 1.5f,  1.5f,  1.5f), std::vector<std::string>{"8"}),
    Point("8", sf::Vector3f(-1.5f,  1.5f,  1.5f))
};
inline std::vector<Point> planePoints = []() {
    std::vector<Point> points;
    for (int x = -100; x <= 100; x += 10) {
        for (int z = -100; z <= 100; z += 10) {
            std::string label = "point_" + std::to_string(x) + "_" + std::to_string(z);
            std::vector<std::string> connections;

            // Connect point to its neighboring points
            if (x + 10 <= 100) connections.push_back("point_" + std::to_string(x + 10) + "_" + std::to_string(z));
            if (z + 10 <= 100) connections.push_back("point_" + std::to_string(x) + "_" + std::to_string(z + 10));

            // Create the point
            points.emplace_back(label, sf::Vector3f(x, 0, z), connections);
        }
    }
    return points;
}();

inline Hitbox tetrahedronBox = Hitbox(4.0f, 4.0f, 4.0f);
inline Hitbox cube1Box = Hitbox(3.f, 3.f, 3.f);
inline Hitbox cube2Box = Hitbox(3.f, 3.f, 3.f);

inline Object tetrahedron = Object(tetrahedronPoints, Position(0, -20, 0, Rotation(0, 0, 0)), tetrahedronBox, sf::Color::Yellow);
inline Object cube1 = Object(cubePoints, Position(0, 0, 0, Rotation(0, 0, 0)), cube1Box, sf::Color::Red);
inline Object cube2 = Object(cubePoints, Position(0, 0, 0, Rotation(0, 0, 0)), cube2Box, sf::Color::Blue);
inline Object plane = Object(planePoints, Position(0, 0, 0, Rotation(0, 0, 0)), Hitbox(), sf::Color::Green, false);

#endif //OBJECTS_H
