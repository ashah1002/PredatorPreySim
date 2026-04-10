#pragma once
#include "nn/neuron.h"
#include "nn/layer.h"
#include <vector>

class Linear : public Layer {
public:
    Linear(int fanIn, int fanOut, bool bias=true, bool randomInit=true);
    ~Linear() = default;

    std::vector<std::vector<float>> getParameters() override;
    void loadParameters(std::vector<std::vector<float>>& params) override;

    std::vector<float> forward(const std::vector<float>& input) override;

private:
    std::vector<Neuron> _neurons;
    int _fanIn;
    int _fanOut;
};
