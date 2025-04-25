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

    Point() : _pos(Vector3(0, 0, 0)) {} // Please don't use this

    explicit Point(const std::string &label, const Vector3 pos)
    : _label(label), _pos(pos) {

        if (label.empty()) {
            throw std::runtime_error("Point label cannot be empty");
        }

        if (!_allPoints.contains(label)) { // Add to all points
            _allPoints.insert(make_pair(this->_label, *this));
        } else {
            throw std::runtime_error("Point already exists");
        }
    }

    explicit Point(const std::string &label, const Vector3 pos, const std::vector<Point>& connections)
    : _label(label), _pos(pos) {

        if (label.empty()) {
            throw std::runtime_error("Point label cannot be empty");
        }

        if (!_allPoints.contains(label)) { // Add to all points
            _allPoints.insert(make_pair(this->_label, *this));
        } else {
            throw std::runtime_error("Point already exists");
        }

        for (auto& connection : connections) { // Add all connections
            addConnection(connection.label());
        }
    }

    explicit Point(const std::string &label, const Vector3 pos, const std::vector<std::string>& connections)
    : _label(label), _pos(pos) {

        if (label.empty()) {
            throw std::runtime_error("Point label cannot be empty");
        }

        if (!_allPoints.contains(label)) { // Add to all points
            _allPoints.insert(make_pair(this->_label, *this));
        } else {
            throw std::runtime_error("Point already exists");
        }

        for (auto& connection : connections) { // Add all connections
            addConnection(connection);
        }
    }

    void addConnection(const std::string& point) {

        if (!_connections.contains(point)) {
            _connections.insert(make_pair(point, point));
        } else {
            throw std::runtime_error("Point already connected");
        }
    }

    void addConnection(const std::vector<std::string>& points) {

        for (auto& point : points) {
            if (!_connections.contains(point)) {
                _connections.insert(make_pair(point, point));
            } else {
                throw std::runtime_error("Point already connected");
            }
        }
    }

    void addConnection(const std::vector<Point>& points) {

        for (auto& point : points) {
            if (!_connections.contains(point.label())) {
                _connections.insert(make_pair(point.label(), point.label()));
            } else {
                throw std::runtime_error("Point already connected");
            }
        }
    }

    std::string label() const {
        return _label;
    }

    std::unordered_map<std::string, std::string> connections() const {
        return _connections;
    }

    Vector3 pos() const {
        return _pos;
    }

private:
    std::unordered_map<std::string, std::string> _connections;
    std::string _label;
    Vector3 _pos;

    static std::unordered_map<std::string, Point> _allPoints;
};

#endif //POINT_H
