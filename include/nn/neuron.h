#pragma once
#include <vector>

class Neuron {
public:
    Neuron(int dim, bool random=true);

    float activate(const std::vector<float>& x);
    std::vector<float> getParameters() const;
    void loadWeights(std::vector<float> weights);

private:
    int _dim;
    std::vector<float> _weights;
    float _bias;
};
