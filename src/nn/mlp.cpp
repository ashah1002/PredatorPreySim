#include "nn/neuron.h"
#include "nn/linear.h"
#include "nn/mlp.h"
#include "nn/relu.h"

MLP::MLP(int inputDims, const std::vector<int>& hiddenDims, int outputDims) {
    if (hiddenDims.empty()) {
        _layers.push_back(std::make_unique<Linear>(inputDims, outputDims));
        return;
    }

    // Input to first hidden layer
    _layers.push_back(std::make_unique<Linear>(inputDims, hiddenDims[0]));
    _layers.push_back(std::make_unique<ReLU>());

    // Internal hidden layers
    for (size_t i = 0; i < hiddenDims.size() - 1; ++i) {
        _layers.push_back(std::make_unique<Linear>(hiddenDims[i], hiddenDims[i+1]));
        _layers.push_back(std::make_unique<ReLU>());
    }

    // Final hidden layer to output
    _layers.push_back(std::make_unique<Linear>(hiddenDims.back(), outputDims));
}