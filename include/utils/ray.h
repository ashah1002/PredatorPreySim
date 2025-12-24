#pragma once 

#include "utils/vector2d.h"

const int RAY_LENGTH = 10;

class Ray {
public:
    Ray(Vector2D origin, Vector2D direction);
    ~Ray();

    Vector2D getOrigin() const;
    Vector2D getDirection() const;

    void setOrigin(Vector2D origin);
    void setDirection(Vector2D direction);
private:
    Vector2D _origin;
    Vector2D _direction;
};
