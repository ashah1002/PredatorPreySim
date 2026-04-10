#include "nn/classifier.h"
#include <algorithm>

Classifier::Classifier(int inputDim, const std::vector<int>& hiddenDims, const std::vector<std::string>& classes)
    : _mlp(inputDim, hiddenDims, static_cast<int>(classes.size())),
      _classes(classes) {}

std::string Classifier::action(const std::vector<float>& inputs) {
    std::vector<float> logits = _mlp.forward(inputs);
    auto maxIt = std::max_element(logits.begin(), logits.end());
    int idx = static_cast<int>(std::distance(logits.begin(), maxIt));
    return _classes[idx];
}
