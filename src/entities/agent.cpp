#include "entities/agent.h"
#include "utils/vector2d.h"
#include <cstdlib>
#include <cmath>

Agent::Agent(Vector2D position)
    : _position(position),
      _velocity(0.0f, 0.0f),
      _maxSpeed(1.0f),
      _radius(1.0f),
      _type(AgentType::PREDATOR),
      _brain()
{
}

float Agent::getRadius() const {
    return _radius;
}

float Agent::getMaxSpeed() const {
    return _maxSpeed;
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

Brain& Agent::getBrain() {
    return _brain;
}

void Agent::update(float tick, const std::vector<float>& visionInput) {
    // Build full input: vision data + normalized velocity
    std::vector<float> fullInput = visionInput;
    fullInput.push_back(_velocity.getX() / _maxSpeed);
    fullInput.push_back(_velocity.getY() / _maxSpeed);

    // Neural network decides velocity delta
    std::vector<float> output = _brain.think(fullInput);

    // Scale output by max speed and apply as acceleration
    Vector2D dv(output[0] * _maxSpeed, output[1] * _maxSpeed);
    _velocity = _velocity + (dv * tick);
    _velocity.capMagnitude(_maxSpeed);
    _position = _position + (_velocity * tick);
}
