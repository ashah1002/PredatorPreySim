#pragma once 

#include "entities/agent.h"
#include "utils/vector2d.h"

const float PREY_MAX_SPEED = 2.0f;
class Prey : public Agent {
public:
    Prey(Vector2D position);
    ~Prey();

private:
    float _radius;
    AgentType _type = AgentType::PREY;
    float _maxSpeed;
};