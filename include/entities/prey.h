#pragma once 

#include "entities/agent.h"
#include "utils/vector2d.h"

class Prey : public Agent {
public:
    Prey(Vector2D position);
    ~Prey();

    Vector2D getPosition() const;

    float getRadius() const;
private:
    float _radius;
    AgentType _type = PREY;

};