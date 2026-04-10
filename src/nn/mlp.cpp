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

std::vector<float> MLP::forward(const std::vector<float>& x) {
    std::vector<float> out = x;
    for (auto& layer : _layers) {
        out = layer->forward(out);
    }
    return out;
}

std::vector<std::vector<std::vector<float>>> MLP::getParameters() {
    std::vector<std::vector<std::vector<float>>> allParams;
    for (auto& layer : _layers) {
        auto params = layer->getParameters();
        if (!params.empty()) {
            allParams.push_back(params);
        }
    }
    return allParams;
}

void MLP::loadParameters(const std::vector<std::vector<std::vector<float>>>& params) {
    size_t paramIdx = 0;
    for (auto& layer : _layers) {
        auto layerParams = layer->getParameters();
        if (!layerParams.empty() && paramIdx < params.size()) {
            auto p = params[paramIdx];
            layer->loadParameters(p);
            paramIdx++;
        }
    }
}
