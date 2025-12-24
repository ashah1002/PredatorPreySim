#pragma once 

class Vector2D {

public:
    
    Vector2D(float x, float y);
    Vector2D();

    float magnitude() const;
    float dot(Vector2D other) const;
    
    bool operator==(const Vector2D& other) const;
    bool operator!=(const Vector2D& other) const;
    bool operator<(const Vector2D& other) const;
    bool operator>(const Vector2D& other) const;
    bool operator<=(const Vector2D& other) const;
    bool operator>=(const Vector2D& other) const;

    Vector2D operator+(const Vector2D& other) const;
    Vector2D operator-(const Vector2D& other) const;
    Vector2D operator*(const float scalar) const;
    Vector2D operator/(const float scalar) const;

    Vector2D& operator+=(const Vector2D& other);
    Vector2D& operator-=(const Vector2D& other);
    Vector2D& operator*=(const float scalar);
    Vector2D& operator/=(const float scalar);

    Vector2D& operator=(const Vector2D& other);

    float getX() const;
    float getY() const;

    void setX(float x);
    void setY(float y);

    float distance(Vector2D other) const;
private:
    float _x;
    float _y;
};