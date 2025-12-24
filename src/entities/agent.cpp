#include "entities/agent.h"
#include "utils/vector2d.h"
#include <cstdlib>

Agent::Agent(Vector2D position) {
    _position = position;
    _velocity = Vector2D(0.0f, 0.0f);
    _radius = 1.0f;
    _maxSpeed = 1.0f;
    _type = AgentType::PREDATOR;
}

Agent::~Agent() {
}

float Agent::getRadius() const {
    return _radius;
}

Vector2D Agent::getPosition() const {
    return _position;


}

Vector2D Agent::getVelocity() const {
    return _velocity;
}

AgentType Agent::getType() const {
    return _type;
}

void Agent::setPosition(Vector2D position) {
    _position = position;
}

void Agent::setVelocity(Vector2D velocity) {
    _velocity = velocity;
}


Vector2D generateRandomDeltaVelocity() {
    return Vector2D(-2.0f + static_cast<float>(rand()) / RAND_MAX * 4.0f, -2.0f + static_cast<float>(rand()) / RAND_MAX * 4.0f);
}
void Agent::update(float tick) {
    Vector2D dv = generateRandomDeltaVelocity();
    _velocity = _velocity + (dv * tick);
    _velocity.capMagnitude(_maxSpeed);
    _position = _position + (_velocity * tick);
}