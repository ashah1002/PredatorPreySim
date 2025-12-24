#include "entities/predator.h"

Predator::Predator(Vector2D position) : Agent(position) {
    _type = AgentType::PREDATOR;
    _maxSpeed = PREDATOR_MAX_SPEED;
    _preyEaten = 0;
    _radius = 2.0f;
}

Predator::~Predator() {
}

void Predator::eatPrey() {
    _preyEaten++;
}

void Predator::resetPreyEaten() {
    _preyEaten = 0;
}

int Predator::getPreyEaten() const {
    return _preyEaten;
}