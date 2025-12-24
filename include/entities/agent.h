#pragma once 

#include "utils/vector2d.h"

enum AgentType {
    PREDATOR,
    PREY
};

class Agent {
public:

    Agent();
    Agent(Vector2D position);
    ~Agent();

    Vector2D getPosition() const;
    Vector2D getVelocity() const;

    float getRadius() const;

    AgentType getType() const;

    void setPosition(Vector2D position);
    void setVelocity(Vector2D velocity);

    void update(float tick);

private:
    Vector2D _position;
    Vector2D _velocity;   
    float _radius;
    AgentType _type;
};