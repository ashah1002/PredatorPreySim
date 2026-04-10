#pragma once

#include "nn/mlp.h"
#include <vector>
#include <cmath>

// Default brain architecture
constexpr int NUM_RAYS = 8;
constexpr float VISION_RANGE = 10.0f;
constexpr int BRAIN_INPUT_DIMS = NUM_RAYS * 2 + 2; // vision + velocity
constexpr int BRAIN_OUTPUT_DIMS = 2;                // velocity delta (dx, dy)

const std::vector<int> BRAIN_HIDDEN_DIMS = {16, 12};

class Brain {
public:
    Brain();
    Brain(const std::vector<std::vector<std::vector<float>>>& weights);
    ~Brain() = default;

    Brain(Brain&&) = default;
    Brain& operator=(Brain&&) = default;

    // Takes vision + velocity input, returns velocity delta with tanh squashing
    std::vector<float> think(const std::vector<float>& inputs);

    std::vector<std::vector<std::vector<float>>> getParameters();
    void loadParameters(const std::vector<std::vector<std::vector<float>>>& params);

    // Mutate weights in-place: each weight has mutationRate chance of being
    // perturbed by uniform noise in [-mutationStrength, mutationStrength]
    void mutate(float mutationRate, float mutationStrength);

private:
    MLP _mlp;
};
