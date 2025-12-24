#pragma once 

#include "utils/vector2d.h"

enum AgentType {
    PREDATOR,
    PREY
};

class Agent {
public:

    Agent(Vector2D position);
    virtual ~Agent();

    Vector2D getPosition() const;
    Vector2D getVelocity() const;

    float getRadius() const;

    AgentType getType() const;

    void setPosition(Vector2D position);
    void setVelocity(Vector2D velocity);

    virtual void update(float tick);

protected:
    Vector2D _position;
    Vector2D _velocity;   
    float _maxSpeed;
    float _radius;
    AgentType _type;
};