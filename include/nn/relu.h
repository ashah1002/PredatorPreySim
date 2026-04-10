#pragma once

#include "nn/layer.h"
#include <vector>
#include <algorithm>

class ReLU : public Layer {
public:
    ReLU() = default;

    std::vector<float> forward(const std::vector<float>& input) override {
        std::vector<float> out;
        out.reserve(input.size());
        for (float val : input) {
            out.push_back(std::max(0.0f, val));
        }
        return out;
    }
};
