#include "entities/prey.h"

Prey::Prey(Vector2D position) : Agent(position) {
    _type = AgentType::PREY;
}

Prey::~Prey() {
}

