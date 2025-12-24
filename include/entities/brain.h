#pragma once 

#include "nn/mlp.h"
#include "utils/ray.h"
#include <vector>

const int INPUT_DIMS = 2;
const int OUTPUT_DIMS = 2;
const std::vector<int> HIDDEN_DIMS = {3, 4, 6};

class Brain {
public:
    Brain();
    Brain(std::vector<float> weights);
    ~Brain();



private:
    MLP _mlp;
};