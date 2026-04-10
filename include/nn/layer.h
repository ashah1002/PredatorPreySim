#pragma once

#include <vector>

class Layer {
public:
    Layer() = default;
    virtual ~Layer() = default;

    virtual std::vector<float> forward(const std::vector<float>& input) = 0;

    virtual std::vector<std::vector<float>> getParameters() { return {}; }
    virtual void loadParameters(std::vector<std::vector<float>>& params) {}
};
