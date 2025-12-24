#include "entities/prey.h"

Prey::Prey(Vector2D position) : Agent(position) {
    _type = AgentType::PREY;
    _radius = 1.0f;
    _maxSpeed = PREY_MAX_SPEED;
}

Prey::~Prey() {
}

