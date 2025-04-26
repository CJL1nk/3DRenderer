//
// Created by CJ on 4/24/2025.
//

#include "Point.h"

std::unordered_map<std::string, Point> Point::_allPoints;

/**
 * Regular constructor method, constructs a standalone point with no connections
 * @param label Point label
 * @param pos Point position relative to object center
 */
Point::Point(const std::string &label, const Vector3 pos)
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

/**
 * Constructs a point with connections to pre-existing points. Will cause errors if points do not already exist
 * @param label Point label
 * @param pos Point position relative to object center
 * @param connections Vector containing points constructed point should be connected to
 */
Point::Point(const std::string &label, const Vector3 pos, const std::vector<Point>& connections)
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

/**
 * Constructs a point with connections to point labels. Will cause errors if points with given labels are NOT constructed before access
 * @param label Point label
 * @param pos Point position relative to object center
 * @param connections Vector containing point labels constructed point should be connected to
 */
Point::Point(const std::string &label, const Vector3 pos, const std::vector<std::string>& connections)
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

/**
 * Adds a connection to a point label. Will cause errors if points with given labels are NOT constructed before access
 * @param point Point label to connect
 */
void Point::addConnection(const std::string& point) {

    if (!_connections.contains(point)) {
        _connections.insert(make_pair(point, point));
    } else {
        throw std::runtime_error("Point already connected");
    }
}

/**
 * Adds a connection to a pre-existing points. Will cause errors if point doesn't already exist
 * @param point Point label to connect
 */
void Point::addConnection(const Point& point) {

    if (!_connections.contains(point.label())) {
        _connections.insert(make_pair(point.label(), point.label()));
    } else {
        throw std::runtime_error("Point already connected");
    }
}

/**
 *  Adds connections to a set of point labels. Will cause errors if points with given labels are NOT constructed before access
 * @param points Vector of point labels to connect
 */
void Point::addConnection(const std::vector<std::string>& points) {

    for (auto& point : points) {
        if (!_connections.contains(point)) {
            _connections.insert(make_pair(point, point));
        } else {
            throw std::runtime_error("Point already connected");
        }
    }
}

/**
 * Adds connections to a set of pre-existing points. Will cause errors if points do not already exist
 * @param points Point label to connect
 */
void Point::addConnection(const std::vector<Point>& points) {

    for (auto& point : points) {
        if (!_connections.contains(point.label())) {
            _connections.insert(make_pair(point.label(), point.label()));
        } else {
            throw std::runtime_error("Point already connected");
        }
    }
}

void Point::setPos(const Vector3& pos) {
    this->_pos = pos;
}

/**
 * Returns point label
 * @return Label of referenced point
 */
std::string Point::label() const {
    return _label;
}

/**
 * Returns map of point label connections
 * @return Map of point label connections
 */
std::unordered_map<std::string, std::string> Point::connections() const {
    return _connections;
}

/**
 * Returns position of referenced point
 * @return Vector containing point X, Y, and Z
 */
Vector3 Point::pos() const {
    return _pos;
}