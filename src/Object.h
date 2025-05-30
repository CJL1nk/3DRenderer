//
// Created by CJ on 4/23/2025.
//

#ifndef OBJECT_H
#define OBJECT_H

#include "includes.h"
#include "types.h"
#include "Point.h"
#include "Hitbox.h"

float degreesToRadians(float degrees);

/**
 * Class defining a generic 3D object
 */
class Object {
public:

    static std::vector<Object*> _allObjects;

    Object(const std::vector<Point> &points, const Position &pos, const Hitbox& hitbox = Hitbox(), const sf::Color& color = sf::Color::White, const bool& showPoints = true);

    void draw(sf::RenderWindow& window);
    void move(Position pos);

    bool collidesWith(const Object& other) const;

    [[nodiscard]] Position getPos() const;
    [[nodiscard]] float getX() const;
    [[nodiscard]] float getY() const;
    [[nodiscard]] float getZ() const;
    [[nodiscard]] Rotation getRotation() const;
    [[nodiscard]] Hitbox getHitbox() const;

    void setPos(Position pos);
    void setX(float x);
    void setY(float y);
    void setZ(float z);
    void setColor(const sf::Color& color = sf::Color::White);

    ~Object() = default;

    void kill() {
        this->~Object();
    }

    Object& operator=(const Object& other);

private:
    Position _pos;
    std::vector<Point> _points;
    sf::Color _color;
    Hitbox _hitbox;
    bool _showPoints;
};

#endif //OBJECT_H
