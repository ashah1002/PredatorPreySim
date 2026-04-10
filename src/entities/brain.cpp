#include "entities/brain.h"

Brain::Brain()
    : _mlp(BRAIN_INPUT_DIMS, BRAIN_HIDDEN_DIMS, BRAIN_OUTPUT_DIMS) {}

Brain::Brain(const std::vector<std::vector<std::vector<float>>>& weights)
    : _mlp(BRAIN_INPUT_DIMS, BRAIN_HIDDEN_DIMS, BRAIN_OUTPUT_DIMS)
{
    _mlp.loadParameters(weights);
}

std::vector<float> Brain::think(const std::vector<float>& inputs) {
    std::vector<float> raw = _mlp.forward(inputs);

    // Apply tanh to bound output to [-1, 1]
    for (float& val : raw) {
        val = std::tanh(val);
    }

    return raw;
}

std::vector<std::vector<std::vector<float>>> Brain::getParameters() {
    return _mlp.getParameters();
}

void Brain::loadParameters(const std::vector<std::vector<std::vector<float>>>& params) {
    _mlp.loadParameters(params);
}
