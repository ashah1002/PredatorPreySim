#pragma once

#include <vector>
#include <string>
#include "nn/mlp.h"

class Classifier {
public:
    Classifier(int inputDim, const std::vector<int>& hiddenDims, const std::vector<std::string>& classes);
    ~Classifier() = default;

    std::string action(const std::vector<float>& inputs);

private:
    MLP _mlp;
    std::vector<std::string> _classes;
};
