#include "entities/vision.h"
#include "entities/agent.h"
#include "engine/spatial_grid.h"
#include "utils/ray.h"
#include <cmath>
#include <limits>

Vision::Vision(VisionConfig config) : _config(config) {}

int Vision::getInputSize() const {
    return _config.numRays * 2;
}

std::vector<float> Vision::sense(const Agent& self, const SpatialGrid& grid) const {
    std::vector<float> inputs;
    inputs.reserve(_config.numRays * 2);

    Vector2D pos = self.getPosition();
    Vector2D vel = self.getVelocity();

    // Heading angle from velocity (default right if stationary)
    float heading = std::atan2(vel.getY(), vel.getX());

    // Query all agents within ray range
    std::vector<Agent*> nearby = grid.query(pos, _config.rayLength);

    for (int i = 0; i < _config.numRays; i++) {
        // Compute ray direction evenly spaced across FOV
        float angle;
        if (_config.numRays == 1) {
            angle = heading;
        } else if (_config.fov >= 6.28f) {
            // Full circle: distribute evenly without overlap
            angle = heading + (6.28318530f * i) / _config.numRays;
        } else {
            angle = heading - _config.fov / 2.0f
                    + (_config.fov * i) / (_config.numRays - 1);
        }

        Vector2D dir(std::cos(angle), std::sin(angle));
        Ray ray(pos, dir);

        float closestDist = _config.rayLength;
        float closestType = 0.0f; // nothing

        for (Agent* other : nearby) {
            if (other == &self) continue;

            float dist = ray.intersectCircle(other->getPosition(), other->getRadius(),
                                             _config.rayLength);
            if (dist >= 0.0f && dist < closestDist) {
                closestDist = dist;
                closestType = (other->getType() == AgentType::PREDATOR) ? -1.0f : 1.0f;
            }
        }

        // Normalized distance: 0 = at agent, 1 = max range / nothing hit
        inputs.push_back(closestDist / _config.rayLength);
        inputs.push_back(closestType);
    }

    return inputs;
}
