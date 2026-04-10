#include "nn/neuron.h"
#include <cstdlib>
#include <cmath>

using namespace std;

float innerProduct(const vector<float>& v1, const vector<float>& v2) {
    if(v1.size() != v2.size()) {
        throw std::invalid_argument("Cannot compute inner product of vectors of differing dimension!");
    }

    float out = 0.0f;

    for(size_t i = 0; i < v1.size(); i++) {
        out += (v1[i] * v2[i]);
    }

    return out;
}


Neuron::Neuron(int dim, bool random) {
    _dim = dim;
    _weights.reserve(dim);

    // He initialization: weights in [-limit, limit] where limit = sqrt(6/dim)
    // Keeps activations well-scaled through ReLU layers
    float limit = std::sqrt(6.0f / static_cast<float>(dim));

    for(int i = 0; i < dim; i++) {
        float val = -limit + static_cast<float>(rand()) / RAND_MAX * 2.0f * limit;
        _weights.push_back(val);
    }

    _bias = 0.0f; // Zero-initialize bias
}

float Neuron::activate(const vector<float>& x) {
    return innerProduct(_weights, x) + _bias;
}

vector<float> Neuron::getParameters() const {
    vector<float> params;

    for(int i = 0; i < _dim; i++) {
        params.push_back(_weights[i]);
    }

    params.push_back(_bias);

    return params;
}

void Neuron::loadWeights(vector<float> weights) {
    if((int)weights.size() != _dim + 1) {
        throw invalid_argument("Weights are not of proper dimension!");
    }

    for(int i = 0; i < _dim; i++) {
        _weights[i] = weights[i];
    }
    _bias = weights[weights.size() - 1];
}
