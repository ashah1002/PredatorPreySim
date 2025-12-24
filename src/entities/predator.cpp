#include "entities/predator.h"

Predator::Predator(Vector2D position) : Agent(position) {
    _type = AgentType::PREDATOR;
}

Predator::~Predator() {
}


