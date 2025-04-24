//
// Created by CJ on 4/24/2025.
//

#ifndef POINT_H
#define POINT_H

#include "includes.h"
#include "types.h"

/**
 * Class describing a point object. Each point knows its own position and which
 * points it's connected to
 * @tparam T Any label type, int or string recommended
 */
class Point {
public:

    Point() : _label("DEFAULT CONSTRUCTED"), _pos(Vector3(0, 0, 0)) {}

    explicit Point(const std::string &label, const Vector3 pos)
    : _label(label), _pos(pos) {

        if (!_allPoints.contains(label)) { // Add to all points
            _allPoints.insert(make_pair(this->_label, *this));
        } else {
            throw std::runtime_error("Point already exists");
        }
    }

    explicit Point(const std::string &label, const Vector3 pos, std::vector<Point> connections)
    : _label(label), _pos(pos) {

        if (!_allPoints.contains(label)) { // Add to all points
            _allPoints.insert(make_pair(this->_label, *this));
        } else {
            throw std::runtime_error("Point already exists");
        }

        for (auto& connection : connections) { // Add all connections
            addConnection(connection);
        }
    }

    explicit Point(const std::string &label, const Vector3 pos, std::vector<std::string> connections)
    : _label(label), _pos(pos) {

        if (!_allPoints.contains(label)) { // Add to all points
            _allPoints.insert(make_pair(this->_label, *this));
        } else {
            throw std::runtime_error("Point already exists");
        }

        for (auto& connection : connections) { // Add all connections
            addConnection(_allPoints[connection]);
        }
    }

    void addConnection(const Point& point) {

        if (!_connections.contains(point.label())) {
            _connections.insert(make_pair(point.label(), point));
        } else {
            throw std::runtime_error("Point already connected");
        }
    }

    std::string label() const {
        return _label;
    }

    std::unordered_map<std::string, Point> connections() const {
        return _connections;
    }

    Vector3 pos() const {
        return _pos;
    }

private:
    std::unordered_map<std::string, Point> _connections;
    std::string _label;
    Vector3 _pos;

    static std::unordered_map<std::string, Point> _allPoints;
};

#endif //POINT_H
