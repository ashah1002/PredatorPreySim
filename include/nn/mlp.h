#pragma once

#include <vector>
#include <memory>
#include "layer.h"

class MLP {
public:
    // Use const reference for input parameters
    MLP(int inputDims, const std::vector<int>& hiddenDims, int outputDims);
    ~MLP() = default; 

    std::vector<std::vector<std::vector<float>>> getParameters();
    void loadParameters(const std::vector<std::vector<std::vector<float>>>& params);

    std::vector<float> forward(const std::vector<float>& x);

private:
    // Store pointers to prevent object slicing
    std::vector<std::unique_ptr<Layer>> _layers;
};