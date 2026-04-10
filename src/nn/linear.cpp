#include "nn/neuron.h"
#include "nn/linear.h"
#include <cstdlib>

using namespace std;

Linear::Linear(int fanIn, int fanOut, bool bias, bool randomInit) {
    _fanIn = fanIn;
    _fanOut = fanOut;

    _neurons.reserve(_fanOut);
    for(int i = 0; i < _fanOut; i++) {
        _neurons.push_back(Neuron(_fanIn));
    }
}

vector<float> Linear::forward(const vector<float>& input) {
    if((int)input.size() != _fanIn) {
        throw invalid_argument("Input must be of size fanIn.");
    }
    vector<float> out;
    out.reserve(_fanOut);

    for(int i = 0; i < _fanOut; i++) {
        out.push_back(_neurons[i].activate(input));
    }
    return out;
}

vector<vector<float>> Linear::getParameters() {
    vector<vector<float>> params;
    for (auto& neuron : _neurons) {
        params.push_back(neuron.getParameters());
    }
    return params;
}

void Linear::loadParameters(vector<vector<float>>& params) {
    if ((int)params.size() != _fanOut) {
        throw invalid_argument("Parameter count must match number of neurons.");
    }
    for (int i = 0; i < _fanOut; i++) {
        _neurons[i].loadWeights(params[i]);
    }
}
