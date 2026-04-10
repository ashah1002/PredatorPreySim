#pragma once

#include <vector>

class Agent;
class SpatialGrid;
class Vector2D;

struct VisionConfig {
    int numRays = 8;
    float rayLength = 10.0f;
    float fov = 6.28318530f; // 2*PI, full circle
};

class Vision {
public:
    Vision(VisionConfig config = VisionConfig());

    // Cast all rays from agent, return flat NN input vector.
    // Per ray: (normalized_distance, type_encoding)
    // type_encoding: -1.0 = predator, 0.0 = nothing, 1.0 = prey
    std::vector<float> sense(const Agent& self, const SpatialGrid& grid) const;

    int getInputSize() const;

private:
    VisionConfig _config;
};
