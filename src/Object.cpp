//
// Created by CJ on 4/23/2025.
//

#include "Object.h"

std::vector<Object*> Object::_allObjects;

/**
 * @param points Object vertices
 * @param pos Object center position
 * @param hitbox Object hitbox
 * @param color Object color
 * @param showPoints Whether object should render its points or not
 */
Object::Object(const std::vector<Point> &points, const Position &pos, const Hitbox& hitbox, const sf::Color& color, const bool& showPoints) {

    this->_pos = pos;
    this->_points = points;
    this->_hitbox = hitbox;
    this->_color = color;
    this->_showPoints = showPoints;

    _allObjects.push_back(this);
}

/**
 * Draws object on screen
 * None of this math is mine thank you random websites and chatGPT for helping me debug the weird stretching
 * AI ended up fixing this entire thing for me cuz objects weren't rotating and things were stretching weirdly
 */
void Object::draw(sf::RenderWindow& window) {
    // Pre-calculate object rotation values in radians
    float yawRad = degreesToRadians(_pos.rotation.yaw);
    float pitchRad = degreesToRadians(_pos.rotation.pitch);
    float rollRad = degreesToRadians(_pos.rotation.roll);

    for (const Point& point : _points) {
        // Get local position
        sf::Vector3f localPos = point.pos();

        // Apply object rotation
        float rotatedX = localPos.x * cos(yawRad) - localPos.z * sin(yawRad);
        float rotatedZ = localPos.x * sin(yawRad) + localPos.z * cos(yawRad);
        localPos.x = rotatedX;
        localPos.z = rotatedZ;

        float rotatedY = localPos.y * cos(pitchRad) - localPos.z * sin(pitchRad);
        rotatedZ = localPos.y * sin(pitchRad) + localPos.z * cos(pitchRad);
        localPos.y = rotatedY;
        localPos.z = rotatedZ;

        float finalX = localPos.x * cos(rollRad) - localPos.y * sin(rollRad);
        float finalY = localPos.x * sin(rollRad) + localPos.y * cos(rollRad);
        localPos.x = finalX;
        localPos.y = finalY;


        sf::Vector3f worldPos = localPos;
        worldPos.x += _pos.x;
        worldPos.y += _pos.y;
        worldPos.z += _pos.z;

        // Calculate camera-relative position
        float camX = worldPos.x - camera.pos.x;
        float camY = worldPos.y - camera.pos.y;
        float camZ = worldPos.z - camera.pos.z;

        // Apply camera yaw
        float tempX = camX * cos(-camera.pos.rotation.yaw) + camZ * sin(-camera.pos.rotation.yaw);
        float tempZ = -camX * sin(-camera.pos.rotation.yaw) + camZ * cos(-camera.pos.rotation.yaw);
        camX = tempX;
        camZ = tempZ;

        // Apply camera pitch
        float tempY = camY * cos(-camera.pos.rotation.pitch) - camZ * sin(-camera.pos.rotation.pitch);
        camZ = camY * sin(-camera.pos.rotation.pitch) + camZ * cos(-camera.pos.rotation.pitch);
        camY = tempY;

        // Apply camera roll
        float finalCamX = camX * cos(-camera.pos.rotation.roll) - camY * sin(-camera.pos.rotation.roll);
        float finalCamY = camX * sin(-camera.pos.rotation.roll) + camY * cos(-camera.pos.rotation.roll);
        float finalCamZ = camZ;

        // Project the point to the screen
        if (finalCamZ + camera.NEAR_PLANE > 0) { // Avoid clipping
            float xProjected = (camera.FOV * finalCamX) / (finalCamZ + camera.NEAR_PLANE) + window.getSize().x / 2;
            float yProjected = (camera.FOV * finalCamY) / (finalCamZ + camera.NEAR_PLANE) + window.getSize().y / 2;

            // Draw point
            if (this->_showPoints) {
                sf::CircleShape shape(3);
                shape.setPosition({xProjected - 3, yProjected - 3});
                shape.setFillColor(sf::Color::White);
                window.draw(shape);
            }
        }
    }


    for (const Point& point : _points) {
        for (const auto& connectionLabel : point.connections()) {
            auto it = std::find_if(_points.begin(), _points.end(), [&](const Point& p) {
                return p.label() == connectionLabel.first;
            });

            if (it != _points.end()) {
                sf::Vector3f localPos1 = point.pos();

                // Apply object rotation
                float rotatedX1 = localPos1.x * cos(yawRad) - localPos1.z * sin(yawRad);
                float rotatedZ1 = localPos1.x * sin(yawRad) + localPos1.z * cos(yawRad);
                localPos1.x = rotatedX1;
                localPos1.z = rotatedZ1;

                float rotatedY1 = localPos1.y * cos(pitchRad) - localPos1.z * sin(pitchRad);
                rotatedZ1 = localPos1.y * sin(pitchRad) + localPos1.z * cos(pitchRad);
                localPos1.y = rotatedY1;
                localPos1.z = rotatedZ1;

                float finalX1 = localPos1.x * cos(rollRad) - localPos1.y * sin(rollRad);
                float finalY1 = localPos1.x * sin(rollRad) + localPos1.y * cos(rollRad);
                localPos1.x = finalX1;
                localPos1.y = finalY1;

                sf::Vector3f worldPos1 = localPos1;
                worldPos1.x += _pos.x;
                worldPos1.y += _pos.y;
                worldPos1.z += _pos.z;

                float camX1 = worldPos1.x - camera.pos.x;
                float camY1 = worldPos1.y - camera.pos.y;
                float camZ1 = worldPos1.z - camera.pos.z;

                float tempX1 = camX1 * cos(-camera.pos.rotation.yaw) + camZ1 * sin(-camera.pos.rotation.yaw);
                float tempZ1 = -camX1 * sin(-camera.pos.rotation.yaw) + camZ1 * cos(-camera.pos.rotation.yaw);
                camX1 = tempX1;
                camZ1 = tempZ1;

                float tempY1 = camY1 * cos(-camera.pos.rotation.pitch) - camZ1 * sin(-camera.pos.rotation.pitch);
                camZ1 = camY1 * sin(-camera.pos.rotation.pitch) + camZ1 * cos(-camera.pos.rotation.pitch);
                camY1 = tempY1;

                float finalCamX1 = camX1 * cos(-camera.pos.rotation.roll) - camY1 * sin(-camera.pos.rotation.roll);
                float finalCamY1 = camX1 * sin(-camera.pos.rotation.roll) + camY1 * cos(-camera.pos.rotation.roll);
                float finalCamZ1 = camZ1;

                float xProj1 = (camera.FOV * finalCamX1) / (finalCamZ1 + camera.NEAR_PLANE) + window.getSize().x / 2;
                float yProj1 = (camera.FOV * finalCamY1) / (finalCamZ1 + camera.NEAR_PLANE) + window.getSize().y / 2;


                sf::Vector3f localPos2 = it->pos();

                // Apply object rotation
                float rotatedX2 = localPos2.x * cos(yawRad) - localPos2.z * sin(yawRad);
                float rotatedZ2 = localPos2.x * sin(yawRad) + localPos2.z * cos(yawRad);
                localPos2.x = rotatedX2;
                localPos2.z = rotatedZ2;

                float rotatedY2 = localPos2.y * cos(pitchRad) - localPos2.z * sin(pitchRad);
                rotatedZ2 = localPos2.y * sin(pitchRad) + localPos2.z * cos(pitchRad);
                localPos2.y = rotatedY2;
                localPos2.z = rotatedZ2;

                float finalX2 = localPos2.x * cos(rollRad) - localPos2.y * sin(rollRad);
                float finalY2 = localPos2.x * sin(rollRad) + localPos2.y * cos(rollRad);
                localPos2.x = finalX2;
                localPos2.y = finalY2;

                sf::Vector3f worldPos2 = localPos2;
                worldPos2.x += _pos.x;
                worldPos2.y += _pos.y;
                worldPos2.z += _pos.z;

                float camX2 = worldPos2.x - camera.pos.x;
                float camY2 = worldPos2.y - camera.pos.y;
                float camZ2 = worldPos2.z - camera.pos.z;

                float tempX2 = camX2 * cos(-camera.pos.rotation.yaw) + camZ2 * sin(-camera.pos.rotation.yaw);
                float tempZ2 = -camX2 * sin(-camera.pos.rotation.yaw) + camZ2 * cos(-camera.pos.rotation.yaw);
                camX2 = tempX2;
                camZ2 = tempZ2;

                float tempY2 = camY2 * cos(-camera.pos.rotation.pitch) - camZ2 * sin(-camera.pos.rotation.pitch);
                camZ2 = camY2 * sin(-camera.pos.rotation.pitch) + camZ2 * cos(-camera.pos.rotation.pitch);
                camY2 = tempY2;

                float finalCamX2 = camX2 * cos(-camera.pos.rotation.roll) - camY2 * sin(-camera.pos.rotation.roll);
                float finalCamY2 = camX2 * sin(-camera.pos.rotation.roll) + camY2 * cos(-camera.pos.rotation.roll);
                float finalCamZ2 = camZ2;

                float xProj2 = (camera.FOV * finalCamX2) / (finalCamZ2 + camera.NEAR_PLANE) + window.getSize().x / 2;
                float yProj2 = (camera.FOV * finalCamY2) / (finalCamZ2 + camera.NEAR_PLANE) + window.getSize().y / 2;


                // Draw connection line
                if (finalCamZ1 + camera.NEAR_PLANE > 0 && finalCamZ2 + camera.NEAR_PLANE > 0) {
                    sf::Vertex line[] = {
                        sf::Vertex(sf::Vector2f(xProj1, yProj1), _color),
                        sf::Vertex(sf::Vector2f(xProj2, yProj2), _color)
                    };
                    window.draw(line, 2, sf::PrimitiveType::Lines);
                }
            }
        }
    }
}

/**
 * Adds gives position values to object
 * @param pos Values to add
 */
void Object::move(const Position pos) {
    this->_pos.x += pos.x;
    this->_pos.y += pos.y;
    this->_pos.z += pos.z;
    this->_pos.rotation.pitch += pos.rotation.pitch;
    this->_pos.rotation.yaw += pos.rotation.yaw;
    this->_pos.rotation.roll += pos.rotation.roll;
}

/**
 * Checks if 2 objects hitboxes collide with each other
 * @param other Object to test collision with
 * @return true if they collide, false otherwise
 */
bool Object::collidesWith(const Object &other) const {

    if (abs(this->getX() - other.getX()) <= (this->getHitbox().getX() / 2.f) + (other.getHitbox().getX() / 2.f) &&
           (abs(this->getY() - other.getY()) <= (this->getHitbox().getY() / 2.f) + (other.getHitbox().getY() / 2.f)) &&
           abs(this->getZ() - other.getZ()) <= (this->getHitbox().getZ() / 2.f) + (other.getHitbox().getZ() / 2.f)) {
        return true;
    }

    return false;
}

/**
 * Returns object's position
 * @return Object's position object
 */
Position Object::getPos() const{
    return this->_pos;
}

/**
 * Returns object's X position
 * @return Object's X position
 */
float Object::getX() const {
    return this->_pos.x;
}

/**
 * Returns object's Y position
 * @return Object's Y position
 */
float Object::getY() const {
    return this->_pos.y;
}

/**
 * Returns object's Z position
 * @return Object's Z position
 */
float Object::getZ() const {
    return this->_pos.z;
}

/**
 * Returns object's Rotation
 * @return Object's Rotation object
 */
Rotation Object::getRotation() const {
    return this->_pos.rotation;
}

/**
 * Returns object's hitbox
 * @return Object's Hitbox object
 */
Hitbox Object::getHitbox() const {
    return this->_hitbox;
}

/**
 * Moves an object to a given position
 * @param pos Position to move object to
 */
void Object::setPos(const Position pos) {
    this->_pos.x = pos.x;
    this->_pos.y = pos.y;
    this->_pos.z = pos.z;
    this->_pos.rotation = pos.rotation;
}

/**
 * Sets an objects X position
 * @param x X position to set
 */
void Object::setX(float x) {
    this->_pos.x = x;
}

/**
 * Sets an objects Y position
 * @param y Y position to set
 */
void Object::setY(float y) {
    this->_pos.y = y;
}

/**
 * Sets an objects Z position
 * @param z Z position to set
 */
void Object::setZ(float z) {
    this->_pos.z = z;
}

/**
 * Sets the edge colors of an object
 * @param color Color to set
 */
void Object::setColor(const sf::Color& color) {
    _color = color;
}

/**
 * Allows for copy of object
 * @param other Object to copy from
 * @return Object copy
 */
Object& Object::operator=(const Object& other) = default;

/**
 * Converts degrees to radians, for calculating object projection and position
 * @param degrees Degrees to convert
 * @return Given degrees in radians
 */
float degreesToRadians(const float degrees) {
    return degrees * M_PI / 180.0f;
}
