#pragma once 

#include "entities/agent.h"
#include "utils/vector2d.h"

class Predator : public Agent {
public:
    Predator(Vector2D position);
    ~Predator();

    Vector2D getPosition() const;

private:
    float _radius;
    AgentType _type = PREDATOR;

};