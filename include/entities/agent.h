#pragma once

#include "utils/vector2d.h"
#include "entities/brain.h"
#include <vector>
#include <memory>

enum AgentType {
    PREDATOR,
    PREY
};

class Agent {
public:

    Agent(Vector2D position);
    virtual ~Agent() = default;

    Agent(Agent&&) = default;
    Agent& operator=(Agent&&) = default;
    Agent(const Agent&) = delete;
    Agent& operator=(const Agent&) = delete;

    Vector2D getPosition() const;
    Vector2D getVelocity() const;

    float getRadius() const;
    float getMaxSpeed() const;

    AgentType getType() const;

    void setPosition(Vector2D position);
    void setVelocity(Vector2D velocity);

    // Update with neural network: vision input from raycasting
    virtual void update(float tick, const std::vector<float>& visionInput);

    Brain& getBrain();

protected:
    Vector2D _position;
    Vector2D _velocity;
    float _maxSpeed;
    float _radius;
    AgentType _type;
    Brain _brain;
};
