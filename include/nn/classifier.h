#pragma once

#include <vector>
#include <string>
#include <memory>
#include "nn/mlp.h"

class Classifier {
public:
    // Use const reference for input parameters
    Classifier(int inputDim, const vector<int>& hiddenDims, const vector<string>& classes);
    ~Classifier() = default; 

    string action(vector<float> inputs);

private:
  //  MLP _mlp;
};