//
// Created by CJ on 4/24/2025.
//

#ifndef POINT_H
#define POINT_H

#include "includes.h"
#include "types.h"

/**
 * Class defining a point object. Each point knows its own position and which
 * points it's connected to
 */
class Point {
public:

    Point() : _pos(Vector3(0, 0, 0)) {} // Please don't use this

    explicit Point(const std::string &label, const Vector3 pos);
    explicit Point(const std::string &label, const Vector3 pos, const std::vector<Point>& connections);
    explicit Point(const std::string &label, const Vector3 pos, const std::vector<std::string>& connections);

    void addConnection(const std::string& point);
    void addConnection(const Point& point);
    void addConnection(const std::vector<std::string>& points);
    void addConnection(const std::vector<Point>& points);

    std::string label() const;
    std::unordered_map<std::string, std::string> connections() const;
    Vector3 pos() const;

private:
    std::unordered_map<std::string, std::string> _connections;
    std::string _label;
    Vector3 _pos;

    static std::unordered_map<std::string, Point> _allPoints;
};

#endif //POINT_H
