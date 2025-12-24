#pragma once 

#include "entities/agent.h"
#include "utils/vector2d.h"

const float PREDATOR_MAX_SPEED = 4.0f;

class Predator : public Agent {
public:
    Predator(Vector2D position);
    ~Predator();

    void eatPrey();
    int getPreyEaten() const;
    void resetPreyEaten();

private:
    int _preyEaten;
    float _radius;
    AgentType _type = PREDATOR;
    float _maxSpeed;
};