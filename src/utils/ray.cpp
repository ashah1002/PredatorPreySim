#include "utils/ray.h"
#include <cmath>

Ray::Ray(Vector2D origin, Vector2D direction)
    : _origin(origin), _direction(direction) {}

Vector2D Ray::getOrigin() const { return _origin; }
Vector2D Ray::getDirection() const { return _direction; }

void Ray::setOrigin(Vector2D origin) { _origin = origin; }
void Ray::setDirection(Vector2D direction) { _direction = direction; }

float Ray::intersectCircle(Vector2D center, float radius, float maxDist) const {
    // Vector from ray origin to circle center
    Vector2D oc = center - _origin;

    // Project oc onto ray direction
    float tca = oc.dot(_direction);

    // Perpendicular distance squared from center to ray
    float d2 = oc.dot(oc) - tca * tca;
    float r2 = radius * radius;

    if (d2 > r2) return -1.0f; // Ray misses the circle

    float thc = std::sqrt(r2 - d2);

    // Two intersection points
    float t0 = tca - thc;
    float t1 = tca + thc;

    // Take the nearest positive intersection
    float t = t0;
    if (t < 0.0f) t = t1;
    if (t < 0.0f || t > maxDist) return -1.0f;

    return t;
}
