#pragma once

#include "entities/agent.h"
#include "utils/vector2d.h"

constexpr float PREY_MAX_SPEED = 2.0f;

class Prey : public Agent {
public:
    Prey(Vector2D position);
    ~Prey() = default;

    Prey(Prey&&) = default;
    Prey& operator=(Prey&&) = default;
};
