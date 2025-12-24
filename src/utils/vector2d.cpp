#include "utils/vector2d.h"
#include <cmath>

Vector2D::Vector2D(float x, float y) : _x(x), _y(y) {}

Vector2D::Vector2D() : _x(0.0f), _y(0.0f) {}

float Vector2D::magnitude() const {
    return sqrt(_x * _x + _y * _y);
}

float Vector2D::dot(Vector2D other) const {
    return _x * other.getX() + _y * other.getY();
}

bool Vector2D::operator==(const Vector2D& other) const {
    return _x == other.getX() && _y == other.getY();
}

bool Vector2D::operator!=(const Vector2D& other) const {
    return _x != other.getX() || _y != other.getY();
}

bool Vector2D::operator<(const Vector2D& other) const {
    return _x < other.getX() && _y < other.getY();
}

bool Vector2D::operator>(const Vector2D& other) const {
    return _x > other.getX() && _y > other.getY();
}

bool Vector2D::operator<=(const Vector2D& other) const {
    return _x <= other.getX() && _y <= other.getY();
}

bool Vector2D::operator>=(const Vector2D& other) const {
    return _x >= other.getX() && _y >= other.getY();
}

Vector2D Vector2D::operator+(const Vector2D& other) const {
    return Vector2D(_x + other.getX(), _y + other.getY());
}   

Vector2D Vector2D::operator-(const Vector2D& other) const {
    return Vector2D(_x - other.getX(), _y - other.getY());
}

Vector2D Vector2D::operator*(const float scalar) const {
    return Vector2D(_x * scalar, _y * scalar);
}

Vector2D Vector2D::operator/(const float scalar) const {
    return Vector2D(_x / scalar, _y / scalar);
}

Vector2D& Vector2D::operator+=(const Vector2D& other) {
    _x += other.getX();
    _y += other.getY();
    return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& other) {
    _x -= other.getX();
    _y -= other.getY();
    return *this;
}

Vector2D& Vector2D::operator*=(const float scalar) {
    _x *= scalar;
    _y *= scalar;
    return *this;
}

Vector2D& Vector2D::operator/=(const float scalar) {
    _x /= scalar;
    _y /= scalar;
    return *this;
}

Vector2D& Vector2D::operator=(const Vector2D& other) {
    _x = other.getX();
    _y = other.getY();
    return *this;
}

float Vector2D::getX() const {
    return _x;
}

float Vector2D::getY() const {
    return _y;
}

void Vector2D::setX(float x) {
    _x = x;
}

void Vector2D::setY(float y) {
    _y = y;
}

float Vector2D::distance(Vector2D other) const {
    return sqrt(pow(other.getX() - _x, 2) + pow(other.getY() - _y, 2));
}