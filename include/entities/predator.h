#pragma once

#include "entities/agent.h"
#include "utils/vector2d.h"

constexpr float PREDATOR_MAX_SPEED = 4.0f;

class Predator : public Agent {
public:
    Predator(Vector2D position);
    ~Predator() = default;

    Predator(Predator&&) = default;
    Predator& operator=(Predator&&) = default;

    void eatPrey();
    int getPreyEaten() const;
    void resetPreyEaten();

private:
    int _preyEaten;
};
