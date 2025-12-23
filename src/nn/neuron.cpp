#include "nn/neuron.h"
#include <cstdlib>

using namespace std;

const int SEED = 42;

float innerProduct(vector<float> v1, vector<float> v2) {
    if(v1.size() != v2.size()) {
        throw std::invalid_argument("Cannot compute inner product of vectors of differing dimension!");
    }

    float out = 0.0f;

    for(int i = 0; i < v1.size(); i++) {
        out += (v1[i] * v2[i]);
    }

    return out;
}


Neuron::Neuron(int dim, bool random) {
    srand(static_cast<unsigned>(SEED));
    _dim = dim;
    _weights.reserve(dim);
    
    for(int i = 0; i < dim; i++) {
        float val = -2.0f + static_cast<float>(rand()) / RAND_MAX * 4.0f;
        _weights.push_back(val);
    }
    
    float val = -2.0f + static_cast<float>(rand()) / RAND_MAX * 4.0f;
    _bias = val;
}

float Neuron::activate(vector<float> x) {
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
    if(weights.size() != _dim + 1) {
        throw invalid_argument("Weights are not of proper dimension!");
    }

    for(int i = 0; i < _dim; i++) {
        _weights[i] = weights[i];
    }
    _bias = weights[weights.size() - 1];
}