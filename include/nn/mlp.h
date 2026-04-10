#pragma once

#include <vector>
#include <memory>
#include "layer.h"

class MLP {
public:
    MLP(int inputDims, const std::vector<int>& hiddenDims, int outputDims);
    ~MLP() = default;

    MLP(MLP&&) = default;
    MLP& operator=(MLP&&) = default;
    MLP(const MLP&) = delete;
    MLP& operator=(const MLP&) = delete;

    std::vector<std::vector<std::vector<float>>> getParameters();
    void loadParameters(const std::vector<std::vector<std::vector<float>>>& params);

    std::vector<float> forward(const std::vector<float>& x);

private:
    std::vector<std::unique_ptr<Layer>> _layers;
};
