#pragma once

#include "utils/vector2d.h"

struct RayHit {
    float distance;  // Raw distance to hit point
    bool hit;        // Whether something was hit
};

class Ray {
public:
    Ray(Vector2D origin, Vector2D direction);

    Vector2D getOrigin() const;
    Vector2D getDirection() const;

    void setOrigin(Vector2D origin);
    void setDirection(Vector2D direction);

    // Test intersection with a circle. Returns distance to hit or -1 if no hit.
    float intersectCircle(Vector2D center, float radius, float maxDist) const;

private:
    Vector2D _origin;
    Vector2D _direction; // Must be unit length
};
